//
// Created by Neko on 02.03.2025.
//

#include "virtual.h"

#include <string.h>
#include <kdbg/debug_print.h>
#include <ke/error.h>

#include "common.h"
#include "physical.h"

/* The hole will be big enough that we don't need to free it for now. */
struct KVIRTUAL_MEMORY_DESCRIPTOR_ENTRY kernelVmde;
PVOID kernelPageMap = NULL;

KERNEL_API void MiInitializeVirtualMemory() {
    PREVENT_DOUBLE_INIT
    ULONGLONG ullHighestPhysicalAddress = MmGetHighestPhysicalAddress();
    ULONGLONG ullHigherHalfMemoryOffset = MmGetMemoryOffset();

    kernelVmde.Base   = ullHigherHalfMemoryOffset + ullHighestPhysicalAddress;
    kernelVmde.Length = MmGetKernelAddressVirtual() - kernelVmde.Base;

    KeDebugPrint("Base address: %llx Length: %0.12f (GB)\n", kernelVmde.Base, (float)kernelVmde.Length / 1024 / 1024 / 1024);

    // Get the kernel page map.
    ULONGLONG ControlRegister3 = 0;
    asm volatile("mov %%cr3, %0" : "=r"(ControlRegister3));
    ControlRegister3 &= ~0xfff; // Get physical address

    kernelPageMap = (PVOID) ControlRegister3;

    KeDebugPrint("Virtual memory initialized\n");
}

KERNEL_API STATUS MiMapPage(
    enum KVM_SECURITY Security,
    enum KVM_MI_PAGING_FLAGS PagingFlags,
    PVOID Physical,
    PVOID Virtual,
    PVOID Pagemap /* Side note: it must be virtual. its universal*/)
{
    if ((ULONGLONG)Physical % PAGE_SIZE != 0) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }
    if ((ULONGLONG)Virtual % PAGE_SIZE != 0) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if (((ULONGLONG)Virtual & 0xFFFF000000000000ULL) != 0 &&
        ((ULONGLONG)Virtual & 0xFFFF000000000000ULL) != 0xFFFF000000000000ULL) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    BOOL NoExecute  = (Security & VMS_NO_EXECUTE)  != 0;
    BOOL ReadWrite  = (Security & VMS_READ_WRITE)  != 0;
    BOOL Supervisor = (Security & VMS_SUPERVISOR)  != 0;

    BOOL WriteThrough = (PagingFlags & VMMIPF_PAGE_WRITE_THROUGH) != 0;
    BOOL CacheDisable = (PagingFlags & VMMIPF_PAGE_CACHE_DISABLE) != 0;
    BOOL PageSizeFlag = (PagingFlags & VMMIPF_PAGE_SIZE_FLAG)     != 0;

    ULONGLONG Pml4Index = (((ULONGLONG)Virtual) >> 39) & 0x1FF;
    ULONGLONG PdpIndex  = (((ULONGLONG)Virtual) >> 30) & 0x1FF;
    ULONGLONG PdIndex   = (((ULONGLONG)Virtual) >> 21) & 0x1FF;
    ULONGLONG PtIndex   = (((ULONGLONG)Virtual) >> 12) & 0x1FF;

    ULONGLONG memOffset = MmGetMemoryOffset();

    ULONGLONG *PML4 = (ULONGLONG*)Pagemap;
    ULONGLONG pml4Entry = PML4[Pml4Index];
    ULONGLONG *PDPT;
    if (!(pml4Entry & VMPF_PRESENT)) {
        PVOID newPDPT;
        if (MmAllocatePage(&newPDPT) != STATUS_SUCCESS) {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void*)((ULONGLONG)newPDPT + memOffset), 0, PAGE_SIZE);
        ULONGLONG entry = (ULONGLONG)newPDPT;
        entry |= VMPF_PRESENT;
        if (ReadWrite)
            entry |= VMPF_READ_WRITE;
        if (Supervisor)
            entry |= VMPF_SUPERVISOR;
        PML4[Pml4Index] = entry;
        PDPT = (ULONGLONG*)((ULONGLONG)newPDPT + memOffset);
    } else {
        PDPT = (ULONGLONG*)((pml4Entry & ~(PAGE_SIZE - 1)) + memOffset);
    }

    ULONGLONG pdptEntry = PDPT[PdpIndex];
    ULONGLONG *PD;
    if (!(pdptEntry & VMPF_PRESENT)) {
        PVOID newPD;
        if (MmAllocatePage(&newPD) != STATUS_SUCCESS) {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void*)((ULONGLONG)newPD + memOffset), 0, PAGE_SIZE);
        ULONGLONG entry = (ULONGLONG)newPD;
        entry |= VMPF_PRESENT;
        if (ReadWrite)
            entry |= VMPF_READ_WRITE;
        if (Supervisor)
            entry |= VMPF_SUPERVISOR;
        PDPT[PdpIndex] = entry;
        PD = (ULONGLONG*)((ULONGLONG)newPD + memOffset);
    } else {
        PD = (ULONGLONG*)(((ULONGLONG)pdptEntry & ~(PAGE_SIZE - 1)) + memOffset);
    }

    ULONGLONG pdEntry = PD[PdIndex];
    ULONGLONG *PT;
    if (!(pdEntry & VMPF_PRESENT)) {
        PVOID newPT;
        if (MmAllocatePage(&newPT) != STATUS_SUCCESS) {
            SetLastError(STATUS_INSUFFICIENT_RESOURCES);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memset((void*)((ULONGLONG)newPT + memOffset), 0, PAGE_SIZE);
        ULONGLONG entry = (ULONGLONG)newPT;
        entry |= VMPF_PRESENT;
        if (ReadWrite)
            entry |= VMPF_READ_WRITE;
        if (Supervisor)
            entry |= VMPF_SUPERVISOR;
        PD[PdIndex] = entry;
        PT = (ULONGLONG*)((ULONGLONG)newPT + memOffset);
    } else {
        PT = (ULONGLONG*)(((ULONGLONG)pdEntry & ~(PAGE_SIZE - 1)) + memOffset);
    }

    ULONGLONG ptEntry = PT[PtIndex];
    if (ptEntry & VMPF_PRESENT) {
        SetLastError(STATUS_ALREADY_MAPPED);
        return STATUS_ALREADY_MAPPED;
    }

    ULONGLONG finalEntry = (ULONGLONG)Physical;
    finalEntry |= VMPF_PRESENT;
    if (ReadWrite)
        finalEntry |= VMPF_READ_WRITE;
    if (Supervisor)
        finalEntry |= VMPF_SUPERVISOR;
    if (WriteThrough)
        finalEntry |= VMPF_PAGE_WRITE_THROUGH; // VMPF_PAGE_WRITE_THROUGH.
    if (CacheDisable)
        finalEntry |= VMPF_PAGE_CACHE_DISABLE; // VMPF_PAGE_CACHE_DISABLE.
    if (NoExecute)
        finalEntry |= VMPF_NO_EXECUTE; // VMPF_NO_EXECUTE.
    if (PageSizeFlag)
        finalEntry |= VMPF_PAGE_SIZE;  // VMPF_PAGE_SIZE.

    PT[PtIndex] = finalEntry;

    MmInvalidatePages(Virtual, PAGE_SIZE);

    return STATUS_SUCCESS;
}

KERNEL_API STATUS MmInvalidatePages(PVOID Virtual, SIZE_T Length)
{
    if (((ULONGLONG)Virtual % PAGE_SIZE) != 0) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if ((Length % PAGE_SIZE) != 0) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    if ((((ULONGLONG)Virtual) & 0xFFFF000000000000ULL) != 0 &&
        (((ULONGLONG)Virtual) & 0xFFFF000000000000ULL) != 0xFFFF000000000000ULL) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
        }

    ULONGLONG addr = (ULONGLONG)Virtual;
    ULONGLONG end = addr + Length;
    for (; addr < end; addr += PAGE_SIZE) {
        __asm__ volatile("invlpg (%0)" : : "r"((void*)addr) : "memory");
    }

    return STATUS_SUCCESS;
}


KERNEL_API void MiGetKernelVirtualMemoryDescriptor(PKVIRTUAL_MEMORY_DESCRIPTOR_ENTRY* Descriptor) {
    *Descriptor = &kernelVmde;
}

KERNEL_API void MiGetKernelPageMapAddressPhysical(PVOID* PageMap) {
    *PageMap = kernelPageMap;
}

KERNEL_API void MiGetKernelPageMapAddressVirtual(PVOID* PageMap) {
    *PageMap = (kernelPageMap + MmGetMemoryOffset());
}