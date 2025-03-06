//
// Created by Neko on 01.03.2025.
//

#include "physical.h"
#include <rtl/limine.h>

#include <kdbg/debug_print.h>
#include <ke/bugcheck.h>
#include <ke/error.h>
#include <rtl/spinlock.h>

#include "common.h"

volatile struct limine_memmap_request memoryMapRequest = {.id = LIMINE_MEMMAP_REQUEST, .revision = 0, .response = NULL};

struct MM_FREELIST_ENTRY;
typedef struct MM_FREELIST_ENTRY *PMM_FREELIST_ENTRY;

struct MM_FREELIST_ENTRY
{
    SIZE_T PageCount;
    PMM_FREELIST_ENTRY Next;
};

static struct MM_FREELIST_ENTRY *FreeListHead = NULL;

struct KSPINLOCK slAllocatePage;
struct KSPINLOCK slDeallocatePage;

static BOOL KiIsMemoryMapValid()
{
    return memoryMapRequest.response != NULL;
}

static enum KMEMORY_MAP_ENTRY_TYPE KiLimineMemoryMapEntryTypeToMDOS(uint64_t EntryType)
{
    switch (EntryType)
    {
    case LIMINE_MEMMAP_USABLE:
        return MMET_USABLE;
    case LIMINE_MEMMAP_RESERVED:
        return MMET_RESERVED;
    case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
        return MMET_ACPI_RECLAIMABLE;
    case LIMINE_MEMMAP_ACPI_NVS:
        return MMET_ACPI_NVS;
    case LIMINE_MEMMAP_BAD_MEMORY:
        return MMET_BAD_MEMORY;
    case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
        return MMET_BOOTLOADER_RECLAIMABLE;
    case LIMINE_MEMMAP_KERNEL_AND_MODULES:
        return MMET_KERNEL_AND_MODULES;
    case LIMINE_MEMMAP_FRAMEBUFFER:
        return MMET_FRAMEBUFFER;
    default:
        return MMET_BAD_MEMORY;
    }
}

KERNEL_API LPSTR StringifyMemoryMapEntryType(enum KMEMORY_MAP_ENTRY_TYPE Type)
{
    switch (Type)
    {
    case MMET_USABLE:
        return "Usable";
    case MMET_RESERVED:
        return "Reserved";
    case MMET_ACPI_RECLAIMABLE:
        return "ACPI Reclaimable";
    case MMET_ACPI_NVS:
        return "ACPI NVS";
    case MMET_BAD_MEMORY:
        return "Bad Memory";
    case MMET_BOOTLOADER_RECLAIMABLE:
        return "Bootloader Reclaimable";
    case MMET_KERNEL_AND_MODULES:
        return "Kernel and Modules";
    case MMET_FRAMEBUFFER:
        return "Framebuffer";
    default:
        return "Unknown";
    }
}

KERNEL_API SIZE_T MmGetMemoryMapEntryCount()
{
    if (KiIsMemoryMapValid())
        return memoryMapRequest.response->entry_count;
    return 0;
}

KERNEL_API STATUS MmGetMemoryMapEntry(PKMEMORY_MAP_ENTRY Entry, SIZE_T Index)
{
    if (!KiIsMemoryMapValid())
    {
        SetLastError(STATUS_FAILURE);
        return STATUS_FAILURE;
    }

    if (Index >= memoryMapRequest.response->entry_count)
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    Entry->Base = memoryMapRequest.response->entries[Index]->base;
    Entry->Length = memoryMapRequest.response->entries[Index]->length;
    Entry->Type = KiLimineMemoryMapEntryTypeToMDOS(memoryMapRequest.response->entries[Index]->type);

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API void MmSummarizeMemoryMap()
{
    SIZE_T EntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY Entry;

    ULONGLONG Usable = 0, Reserved = 0, AcpiReclaimable = 0, AcpiNvs = 0, Bad = 0, BootloaderReclaimable = 0,
              KernelAndModules = 0, Framebuffer = 0, Overall = 0;

    KeDebugPrint("\n=== Memory Map Summary ===\n");
    KeDebugPrint("Index |   Base Address   |   End Address    |    Size (KB)    |              Type              \n");
    KeDebugPrint("------+------------------+------------------+-----------------+--------------------------------\n");

    for (SIZE_T i = 0; i < EntryCount; i++)
    {
        STATUS Status = MmGetMemoryMapEntry(&Entry, i);
        if (Status != STATUS_SUCCESS)
        {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        ULONGLONG EndAddress = Entry.Base + Entry.Length;
        ULONGLONG SizeInKilobytes = Entry.Length / 1024;
        const char *StringifiedType = StringifyMemoryMapEntryType(Entry.Type);

        KeDebugPrint("%4zu  |  %014llx  |  %014llx  |  %10llu KB  |  %-15s\n", i, Entry.Base, EndAddress,
                     SizeInKilobytes, StringifiedType);

        // Exclude reserved memory from overall usable count
        if (Entry.Type != MMET_RESERVED)
            Overall += Entry.Length;

        // Sum memory per type
        switch (Entry.Type)
        {
        case MMET_USABLE:
            Usable += Entry.Length;
            break;
        case MMET_RESERVED:
            Reserved += Entry.Length;
            break;
        case MMET_ACPI_RECLAIMABLE:
            AcpiReclaimable += Entry.Length;
            break;
        case MMET_ACPI_NVS:
            AcpiNvs += Entry.Length;
            break;
        case MMET_BAD_MEMORY:
            Bad += Entry.Length;
            break;
        case MMET_BOOTLOADER_RECLAIMABLE:
            BootloaderReclaimable += Entry.Length;
            break;
        case MMET_KERNEL_AND_MODULES:
            KernelAndModules += Entry.Length;
            break;
        case MMET_FRAMEBUFFER:
            Framebuffer += Entry.Length;
            break;
        default:
            break;
        }
    }

    KeDebugPrint("\n=== Memory Summary ===\n");
    KeDebugPrint("Total Usable Memory:           %10llu KB\n", Usable / 1024);
    KeDebugPrint("Reserved Memory:               %10llu KB\n", Reserved / 1024);
    KeDebugPrint("ACPI Reclaimable Memory:       %10llu KB\n", AcpiReclaimable / 1024);
    KeDebugPrint("ACPI NVS Memory:               %10llu KB\n", AcpiNvs / 1024);
    KeDebugPrint("Bad Memory:                    %10llu KB\n", Bad / 1024);
    KeDebugPrint("Bootloader Reclaimable Memory: %10llu KB\n", BootloaderReclaimable / 1024);
    KeDebugPrint("Kernel and Modules:            %10llu KB\n", KernelAndModules / 1024);
    KeDebugPrint("Framebuffer Memory:            %10llu KB\n", Framebuffer / 1024);
    KeDebugPrint("=========================================\n");
    KeDebugPrint("Overall Usable Memory:         %10llu KB\n", Overall / 1024);

    // Convert sizes to percentages
    double OverallMB = (double)Overall / (1024 * 1024);
    double UsablePerc = ((double)Usable / Overall) * 100.0;
    double AcpiReclaimablePerc = ((double)AcpiReclaimable / Overall) * 100.0;
    double AcpiNvsPerc = ((double)AcpiNvs / Overall) * 100.0;
    double BadPerc = ((double)Bad / Overall) * 100.0;
    double BootloaderReclaimablePerc = ((double)BootloaderReclaimable / Overall) * 100.0;
    double KernelAndModulesPerc = ((double)KernelAndModules / Overall) * 100.0;
    double FramebufferPerc = ((double)Framebuffer / Overall) * 100.0;

    KeDebugPrint("\n=== Memory Summary (Excluding Reserved) ===\n");
    KeDebugPrint("Total Usable Memory:           %10llu KB (%.6f%%)\n", Usable / 1024, UsablePerc);
    KeDebugPrint("ACPI Reclaimable Memory:       %10llu KB (%.6f%%)\n", AcpiReclaimable / 1024, AcpiReclaimablePerc);
    KeDebugPrint("ACPI NVS Memory:               %10llu KB (%.6f%%)\n", AcpiNvs / 1024, AcpiNvsPerc);
    KeDebugPrint("Bad Memory:                    %10llu KB (%.6f%%)\n", Bad / 1024, BadPerc);
    KeDebugPrint("Bootloader Reclaimable Memory: %10llu KB (%.6f%%)\n", BootloaderReclaimable / 1024,
                 BootloaderReclaimablePerc);
    KeDebugPrint("Kernel and Modules:            %10llu KB (%.6f%%)\n", KernelAndModules / 1024, KernelAndModulesPerc);
    KeDebugPrint("Framebuffer Memory:            %10llu KB (%.6f%%)\n", Framebuffer / 1024, FramebufferPerc);
    KeDebugPrint("===========================================\n");
    KeDebugPrint("Overall Usable Memory:         %.2f MB\n", OverallMB);
}

KERNEL_API void KiInitializePhysicalMemoryManager()
{
    PREVENT_DOUBLE_INIT
    KeDebugPrint("Initializing physical memory manager...\n");

    // Initialize spinlocks
    KiCreateSpinLock(&slAllocatePage);
    KiCreateSpinLock(&slDeallocatePage);

    if (!KiIsMemoryMapValid())
    {
        KeDebugPrint("Memory map not available.\n");
        SetLastError(STATUS_FAILURE);
        KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
    }

    FreeListHead = NULL;
    SIZE_T EntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY Entry;

    for (SIZE_T i = 0; i < EntryCount; i++)
    {
        STATUS Status = MmGetMemoryMapEntry(&Entry, i);
        if (Status != STATUS_SUCCESS)
        {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        if (Entry.Type == MMET_USABLE)
        {
            ULONGLONG Base = Entry.Base;
            ULONGLONG Length = Entry.Length;

            // First full page starts at the next page boundary after base
            ULONGLONG StartPageIndex = (Base + PAGE_SIZE - 1) / PAGE_SIZE;
            ULONGLONG StartAddress = StartPageIndex * PAGE_SIZE;

            // Last full page ends before or at base + length
            ULONGLONG EndPageIndex = (Base + Length - 1) / PAGE_SIZE;
            ULONGLONG EndAddress = EndPageIndex * PAGE_SIZE + PAGE_SIZE;

            // Check if there are full pages within the region
            if (StartAddress < Base + Length && StartAddress < EndAddress)
            {
                SIZE_T PageCount = (EndPageIndex - StartPageIndex + 1);

                // Place the free list entry at the start of the block
                PMM_FREELIST_ENTRY FreeEntry = (PMM_FREELIST_ENTRY)StartAddress;
                FreeEntry->PageCount = PageCount;
                FreeEntry->Next = FreeListHead;
                FreeListHead = FreeEntry;

                KeDebugPrint("Added free block at %p with %zu pages\n", (PVOID)StartAddress, PageCount);
            }
        }
    }

    KeDebugPrint("Physical memory manager initialized\n");
}

KERNEL_API STATUS MmAllocatePage(PVOID *Block)
{
    KiAcquireSpinlock(&slAllocatePage);
    if (!Block)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        KiReleaseSpinlock(&slAllocatePage);
        return STATUS_INVALID_PARAMETER;
    }

    PMM_FREELIST_ENTRY prev = NULL;
    PMM_FREELIST_ENTRY current = FreeListHead;

    while (current != NULL)
    {
        if (current->PageCount >= 1)
        {
            PVOID allocated_page = (PVOID)current;

            if (current->PageCount == 1)
            {
                // Remove the block from the list
                if (prev == NULL)
                {
                    FreeListHead = current->Next;
                }
                else
                {
                    prev->Next = current->Next;
                }
            }
            else
            {
                // Split the block: move header to next page
                PMM_FREELIST_ENTRY new_entry = (PMM_FREELIST_ENTRY)((PUCHAR)current + PAGE_SIZE);
                new_entry->PageCount = current->PageCount - 1;
                new_entry->Next = current->Next;

                if (prev == NULL)
                {
                    FreeListHead = new_entry;
                }
                else
                {
                    prev->Next = new_entry;
                }
            }

            *Block = allocated_page;
            SetLastError(STATUS_SUCCESS);
            KiReleaseSpinlock(&slAllocatePage);
            return STATUS_SUCCESS;
        }

        prev = current;
        current = current->Next;
    }

    SetLastError(STATUS_OUT_OF_MEMORY);
    KiReleaseSpinlock(&slAllocatePage);
    return STATUS_OUT_OF_MEMORY;
}

KERNEL_API void MmFreePage(PVOID Block)
{
    if (!Block)
    {
        SetLastError(STATUS_INVALID_PARAMETER);
        return;
    }

    KiAcquireSpinlock(&slDeallocatePage);

    PMM_FREELIST_ENTRY free_entry = (PMM_FREELIST_ENTRY)Block;
    free_entry->PageCount = 1;
    free_entry->Next = FreeListHead;
    FreeListHead = free_entry;

    KiReleaseSpinlock(&slDeallocatePage);
    SetLastError(STATUS_SUCCESS);
}

KERNEL_API ULONGLONG MmGetHighestPhysicalAddress()
{
    SIZE_T dEntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY ent;
    ULONGLONG ullHighestAddress = 0;

    for (SIZE_T i = 0; i < dEntryCount; i++)
    {
        STATUS status = MmGetMemoryMapEntry(&ent, i);
        if (status != STATUS_SUCCESS)
        {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        if (ent.Base + ent.Length > ullHighestAddress)
        {
            ullHighestAddress = ent.Base + ent.Length;
        }
    }

    return ullHighestAddress;
}