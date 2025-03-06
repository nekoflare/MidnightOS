//
// Created by Neko on 02.03.2025.
//

#include "virtual.h"

#include <kdbg/debug_print.h>
#include <ke/error.h>
#include <string.h>

#include "common.h"
#include "physical.h"

/* The hole will be big enough that we don't need to free it for now. */
struct KVIRTUAL_MEMORY_DESCRIPTOR_ENTRY KernelVmde;
PVOID KernelPageMap = NULL;

KERNEL_API void MiInitializeVirtualMemory()
{
    PREVENT_DOUBLE_INIT
    ULONGLONG HighestPhysicalAddress = MmGetHighestPhysicalAddress();
    ULONGLONG HigherHalfMemoryOffset = MmGetMemoryOffset();

    KernelVmde.Base = HigherHalfMemoryOffset + HighestPhysicalAddress;
    KernelVmde.Length = MmGetKernelAddressVirtual() - KernelVmde.Base;

    KeDebugPrint("Base address: %llx Length: %0.12f (GB)\n", KernelVmde.Base,
                 (float)KernelVmde.Length / 1024 / 1024 / 1024);

    // Get the kernel page map.
    ULONGLONG ControlRegister = 0;
    asm volatile("mov %%cr3, %0" : "=r"(ControlRegister));
    ControlRegister &= ~0xfff; // Get physical address

    KernelPageMap = (PVOID)ControlRegister;

    KeDebugPrint("Virtual memory initialized\n");
}

KERNEL_API STATUS MiMapPage(enum KVM_SECURITY Security, enum KVM_MI_PAGING_FLAGS PagingFlags, PVOID Physical,
                            PVOID Virtual, PVOID Pagemap /* Side note: it must be virtual. its universal*/)
{
    if ((ULONGLONG)Physical % PAGE_SIZE != 0)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }
    if ((ULONGLONG)Virtual % PAGE_SIZE != 0)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if (((ULONGLONG)Virtual & 0xFFFF000000000000ULL) != 0 &&
        ((ULONGLONG)Virtual & 0xFFFF000000000000ULL) != 0xFFFF000000000000ULL)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    BOOL NoExecute = (Security & VMS_NO_EXECUTE) != 0;
    BOOL ReadWrite = (Security & VMS_READ_WRITE) != 0;
    BOOL Supervisor = (Security & VMS_SUPERVISOR) != 0;

    BOOL WriteThrough = (PagingFlags & VMMIPF_PAGE_WRITE_THROUGH) != 0;
    BOOL CacheDisable = (PagingFlags & VMMIPF_PAGE_CACHE_DISABLE) != 0;
    BOOL PageSizeFlag = (PagingFlags & VMMIPF_PAGE_SIZE_FLAG) != 0;

    ULONGLONG Pml4Index = (((ULONGLONG)Virtual) >> 39) & 0x1FF;
    ULONGLONG PdpIndex = (((ULONGLONG)Virtual) >> 30) & 0x1FF;
    ULONGLONG PdIndex = (((ULONGLONG)Virtual) >> 21) & 0x1FF;
    ULONGLONG PtIndex = (((ULONGLONG)Virtual) >> 12) & 0x1FF;

    ULONGLONG MemoryOffset = MmGetMemoryOffset();

    ULONGLONG *PML4 = (ULONGLONG *)Pagemap;
    ULONGLONG PML4Entry = PML4[Pml4Index];
    ULONGLONG *PDPT;
    if (!(PML4Entry & VMPF_PRESENT))
    {
        PVOID NewPDPT;
        if (MmAllocatePage(&NewPDPT) != STATUS_SUCCESS)
        {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void *)((ULONGLONG)NewPDPT + MemoryOffset), 0, PAGE_SIZE);
        ULONGLONG Entry = (ULONGLONG)NewPDPT;
        Entry |= VMPF_PRESENT;
        if (ReadWrite)
            Entry |= VMPF_READ_WRITE;
        if (Supervisor)
            Entry |= VMPF_SUPERVISOR;
        PML4[Pml4Index] = Entry;
        PDPT = (ULONGLONG *)((ULONGLONG)NewPDPT + MemoryOffset);
    }
    else
    {
        PDPT = (ULONGLONG *)((PML4Entry & ~(PAGE_SIZE - 1)) + MemoryOffset);
    }

    ULONGLONG PDPTEntry = PDPT[PdpIndex];
    ULONGLONG *PD;
    if (!(PDPTEntry & VMPF_PRESENT))
    {
        PVOID NewPD;
        if (MmAllocatePage(&NewPD) != STATUS_SUCCESS)
        {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void *)((ULONGLONG)NewPD + MemoryOffset), 0, PAGE_SIZE);
        ULONGLONG Entry = (ULONGLONG)NewPD;
        Entry |= VMPF_PRESENT;
        if (ReadWrite)
            Entry |= VMPF_READ_WRITE;
        if (Supervisor)
            Entry |= VMPF_SUPERVISOR;
        PDPT[PdpIndex] = Entry;
        PD = (ULONGLONG *)((ULONGLONG)NewPD + MemoryOffset);
    }
    else
    {
        PD = (ULONGLONG *)(((ULONGLONG)PDPTEntry & ~(PAGE_SIZE - 1)) + MemoryOffset);
    }

    ULONGLONG PDEntry = PD[PdIndex];
    ULONGLONG *PT;
    if (!(PDEntry & VMPF_PRESENT))
    {
        PVOID NewPT;
        if (MmAllocatePage(&NewPT) != STATUS_SUCCESS)
        {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void *)((ULONGLONG)NewPT + MemoryOffset), 0, PAGE_SIZE);
        ULONGLONG Entry = (ULONGLONG)NewPT;
        Entry |= VMPF_PRESENT;
        if (ReadWrite)
            Entry |= VMPF_READ_WRITE;
        if (Supervisor)
            Entry |= VMPF_SUPERVISOR;
        PD[PdIndex] = Entry;
        PT = (ULONGLONG *)((ULONGLONG)NewPT + MemoryOffset);
    }
    else
    {
        PT = (ULONGLONG *)(((ULONGLONG)PDEntry & ~(PAGE_SIZE - 1)) + MemoryOffset);
    }

    ULONGLONG PTEntry = PT[PtIndex];
    if (PTEntry & VMPF_PRESENT)
    {
        SetLastError(STATUS_ALREADY_MAPPED);
        return STATUS_ALREADY_MAPPED;
    }

    ULONGLONG FinalEntry = (ULONGLONG)Physical;
    FinalEntry |= VMPF_PRESENT;
    if (ReadWrite)
        FinalEntry |= VMPF_READ_WRITE;
    if (Supervisor)
        FinalEntry |= VMPF_SUPERVISOR;
    if (WriteThrough)
        FinalEntry |= VMPF_PAGE_WRITE_THROUGH; // VMPF_PAGE_WRITE_THROUGH.
    if (CacheDisable)
        FinalEntry |= VMPF_PAGE_CACHE_DISABLE; // VMPF_PAGE_CACHE_DISABLE.
    if (NoExecute)
        FinalEntry |= VMPF_NO_EXECUTE; // VMPF_NO_EXECUTE.
    if (PageSizeFlag)
        FinalEntry |= VMPF_PAGE_SIZE; // VMPF_PAGE_SIZE.

    PT[PtIndex] = FinalEntry;

    MmInvalidatePages(Virtual, PAGE_SIZE);

    return STATUS_SUCCESS;
}

KERNEL_API STATUS MmInvalidatePages(PVOID Virtual, SIZE_T Length)
{
    if (((ULONGLONG)Virtual % PAGE_SIZE) != 0)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if ((Length % PAGE_SIZE) != 0)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if ((((ULONGLONG)Virtual) & 0xFFFF000000000000ULL) != 0 &&
        (((ULONGLONG)Virtual) & 0xFFFF000000000000ULL) != 0xFFFF000000000000ULL)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    ULONGLONG Address = (ULONGLONG)Virtual;
    ULONGLONG End = Address + Length;
    for (; Address < End; Address += PAGE_SIZE)
    {
        __asm__ volatile("invlpg (%0)" : : "r"((void *)Address) : "memory");
    }

    return STATUS_SUCCESS;
}

KERNEL_API void MiGetKernelVirtualMemoryDescriptor(PKVIRTUAL_MEMORY_DESCRIPTOR_ENTRY *Descriptor)
{
    *Descriptor = &KernelVmde;
}

KERNEL_API void MiGetKernelPageMapAddressPhysical(PVOID *PageMap)
{
    *PageMap = KernelPageMap;
}

KERNEL_API void MiGetKernelPageMapAddressVirtual(PVOID *PageMap)
{
    *PageMap = (KernelPageMap + MmGetMemoryOffset());
}