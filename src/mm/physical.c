//
// Created by Neko on 01.03.2025.
//

#include <rtl/limine.h>
#include "physical.h"

#include <kdbg/debug_print.h>
#include <ke/bugcheck.h>
#include <ke/error.h>
#include <rtl/spinlock.h>

#include "common.h"

volatile struct limine_memmap_request memoryMapRequest = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL
};

struct MM_FREELIST_ENTRY;
typedef struct MM_FREELIST_ENTRY* PMM_FREELIST_ENTRY;

struct MM_FREELIST_ENTRY {
    SIZE_T PageCount;
    PMM_FREELIST_ENTRY Next;
};

static struct MM_FREELIST_ENTRY* FreeListHead = NULL;

struct KSPINLOCK slAllocatePage;
struct KSPINLOCK slDeallocatePage;

static BOOL KiIsMemoryMapValid() {
    return memoryMapRequest.response != NULL;
}

static enum KMEMORY_MAP_ENTRY_TYPE KiLimineMemoryMapEntryTypeToMDOS(uint64_t entry_type) {
    switch (entry_type) {
        case LIMINE_MEMMAP_USABLE:                  return MMET_USABLE;
        case LIMINE_MEMMAP_RESERVED:                return MMET_RESERVED;
        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:        return MMET_ACPI_RECLAIMABLE;
        case LIMINE_MEMMAP_ACPI_NVS:                return MMET_ACPI_NVS;
        case LIMINE_MEMMAP_BAD_MEMORY:              return MMET_BAD_MEMORY;
        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:  return MMET_BOOTLOADER_RECLAIMABLE;
        case LIMINE_MEMMAP_KERNEL_AND_MODULES:      return MMET_KERNEL_AND_MODULES;
        case LIMINE_MEMMAP_FRAMEBUFFER:             return MMET_FRAMEBUFFER;
        default:                                    return MMET_BAD_MEMORY;
    }
}

KERNEL_API LPSTR StringifyMemoryMapEntryType(enum KMEMORY_MAP_ENTRY_TYPE Type) {
    switch (Type) {
        case MMET_USABLE:                  return "Usable";
        case MMET_RESERVED:                return "Reserved";
        case MMET_ACPI_RECLAIMABLE:        return "ACPI Reclaimable";
        case MMET_ACPI_NVS:                return "ACPI NVS";
        case MMET_BAD_MEMORY:              return "Bad Memory";
        case MMET_BOOTLOADER_RECLAIMABLE:  return "Bootloader Reclaimable";
        case MMET_KERNEL_AND_MODULES:      return "Kernel and Modules";
        case MMET_FRAMEBUFFER:             return "Framebuffer";
        default:                           return "Unknown";
    }
}

KERNEL_API SIZE_T MmGetMemoryMapEntryCount() {
    if (KiIsMemoryMapValid())
        return memoryMapRequest.response->entry_count;
    return 0;
}

KERNEL_API STATUS MmGetMemoryMapEntry(
    PKMEMORY_MAP_ENTRY Entry,
    SIZE_T Index
    ) {
    if (!KiIsMemoryMapValid()) {
        SetLastError(STATUS_FAILURE);
        return STATUS_FAILURE;
    }

    if (Index >= memoryMapRequest.response->entry_count) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    Entry->Base = memoryMapRequest.response->entries[Index]->base;
    Entry->Length = memoryMapRequest.response->entries[Index]->length;
    Entry->Type = KiLimineMemoryMapEntryTypeToMDOS(memoryMapRequest.response->entries[Index]->type);

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API void MmSummarizeMemoryMap() {
    SIZE_T dEntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY ent;

    ULONGLONG   ullUsable = 0,
                ullReserved = 0,
                ullAcpiReclaimable = 0,
                ullAcpiNvs = 0,
                ullBad = 0,
                ullBootloaderReclaimable = 0,
                ullKernelAndModules = 0,
                ullFramebuffer = 0,
                ullOverall = 0;

    KeDebugPrint("\n=== Memory Map Summary ===\n");
    KeDebugPrint("Index |   Base Address   |   End Address    |    Size (KB)    |              Type              \n");
    KeDebugPrint("------+------------------+------------------+-----------------+--------------------------------\n");

    for (SIZE_T i = 0; i < dEntryCount; i++) {
        STATUS status = MmGetMemoryMapEntry(&ent, i);
        if (status != STATUS_SUCCESS) {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        ULONGLONG endAddress = ent.Base + ent.Length;
        ULONGLONG sizeInKB = ent.Length / 1024;
        const char* typeStr = StringifyMemoryMapEntryType(ent.Type);

        KeDebugPrint("%4zu  |  %014llx  |  %014llx  |  %10llu KB  |  %-15s\n",
                     i, ent.Base, endAddress, sizeInKB, typeStr);

        // Exclude reserved memory from overall usable count
        if (ent.Type != MMET_RESERVED)
            ullOverall += ent.Length;

        // Sum memory per type
        switch (ent.Type) {
            case MMET_USABLE:
                ullUsable += ent.Length;
                break;
            case MMET_RESERVED:
                ullReserved += ent.Length;
                break;
            case MMET_ACPI_RECLAIMABLE:
                ullAcpiReclaimable += ent.Length;
                break;
            case MMET_ACPI_NVS:
                ullAcpiNvs += ent.Length;
                break;
            case MMET_BAD_MEMORY:
                ullBad += ent.Length;
                break;
            case MMET_BOOTLOADER_RECLAIMABLE:
                ullBootloaderReclaimable += ent.Length;
                break;
            case MMET_KERNEL_AND_MODULES:
                ullKernelAndModules += ent.Length;
                break;
            case MMET_FRAMEBUFFER:
                ullFramebuffer += ent.Length;
                break;
            default:
                break;
        }
    }

    KeDebugPrint("\n=== Memory Summary ===\n");
    KeDebugPrint("Total Usable Memory:           %10llu KB\n", ullUsable / 1024);
    KeDebugPrint("Reserved Memory:               %10llu KB\n", ullReserved / 1024);
    KeDebugPrint("ACPI Reclaimable Memory:       %10llu KB\n", ullAcpiReclaimable / 1024);
    KeDebugPrint("ACPI NVS Memory:               %10llu KB\n", ullAcpiNvs / 1024);
    KeDebugPrint("Bad Memory:                    %10llu KB\n", ullBad / 1024);
    KeDebugPrint("Bootloader Reclaimable Memory: %10llu KB\n", ullBootloaderReclaimable / 1024);
    KeDebugPrint("Kernel and Modules:            %10llu KB\n", ullKernelAndModules / 1024);
    KeDebugPrint("Framebuffer Memory:            %10llu KB\n", ullFramebuffer / 1024);
    KeDebugPrint("=========================================\n");
    KeDebugPrint("Overall Usable Memory:         %10llu KB\n", ullOverall / 1024);

    // Convert sizes to percentages
    double dOverallMB = (double)ullOverall / (1024 * 1024);
    double dUsablePerc = ((double)ullUsable / ullOverall) * 100.0;
    double dAcpiReclaimablePerc = ((double)ullAcpiReclaimable / ullOverall) * 100.0;
    double dAcpiNvsPerc = ((double)ullAcpiNvs / ullOverall) * 100.0;
    double dBadPerc = ((double)ullBad / ullOverall) * 100.0;
    double dBootloaderReclaimablePerc = ((double)ullBootloaderReclaimable / ullOverall) * 100.0;
    double dKernelAndModulesPerc = ((double)ullKernelAndModules / ullOverall) * 100.0;
    double dFramebufferPerc = ((double)ullFramebuffer / ullOverall) * 100.0;

    KeDebugPrint("\n=== Memory Summary (Excluding Reserved) ===\n");
    KeDebugPrint("Total Usable Memory:           %10llu KB (%.6f%%)\n", ullUsable / 1024, dUsablePerc);
    KeDebugPrint("ACPI Reclaimable Memory:       %10llu KB (%.6f%%)\n", ullAcpiReclaimable / 1024, dAcpiReclaimablePerc);
    KeDebugPrint("ACPI NVS Memory:               %10llu KB (%.6f%%)\n", ullAcpiNvs / 1024, dAcpiNvsPerc);
    KeDebugPrint("Bad Memory:                    %10llu KB (%.6f%%)\n", ullBad / 1024, dBadPerc);
    KeDebugPrint("Bootloader Reclaimable Memory: %10llu KB (%.6f%%)\n", ullBootloaderReclaimable / 1024, dBootloaderReclaimablePerc);
    KeDebugPrint("Kernel and Modules:            %10llu KB (%.6f%%)\n", ullKernelAndModules / 1024, dKernelAndModulesPerc);
    KeDebugPrint("Framebuffer Memory:            %10llu KB (%.6f%%)\n", ullFramebuffer / 1024, dFramebufferPerc);
    KeDebugPrint("===========================================\n");
    KeDebugPrint("Overall Usable Memory:         %.2f MB\n", dOverallMB);
}

KERNEL_API void KiInitializePhysicalMemoryManager() {
    PREVENT_DOUBLE_INIT
    KeDebugPrint("Initializing physical memory manager...\n");

    // Initialize spinlocks
    KiCreateSpinLock(&slAllocatePage);
    KiCreateSpinLock(&slDeallocatePage);

    if (!KiIsMemoryMapValid()) {
        KeDebugPrint("Memory map not available.\n");
        SetLastError(STATUS_FAILURE);
        KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
    }

    FreeListHead = NULL;
    SIZE_T dEntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY ent;

    for (SIZE_T i = 0; i < dEntryCount; i++) {
        STATUS status = MmGetMemoryMapEntry(&ent, i);
        if (status != STATUS_SUCCESS) {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        if (ent.Type == MMET_USABLE) {
            ULONGLONG base = ent.Base;
            ULONGLONG length = ent.Length;

            // First full page starts at the next page boundary after base
            ULONGLONG start_page_index = (base + PAGE_SIZE - 1) / PAGE_SIZE;
            ULONGLONG start_address = start_page_index * PAGE_SIZE;

            // Last full page ends before or at base + length
            ULONGLONG end_page_index = (base + length - 1) / PAGE_SIZE;
            ULONGLONG end_address = end_page_index * PAGE_SIZE + PAGE_SIZE;

            // Check if there are full pages within the region
            if (start_address < base + length && start_address < end_address) {
                SIZE_T page_count = (end_page_index - start_page_index + 1);

                // Place the free list entry at the start of the block
                PMM_FREELIST_ENTRY free_entry = (PMM_FREELIST_ENTRY)start_address;
                free_entry->PageCount = page_count;
                free_entry->Next = FreeListHead;
                FreeListHead = free_entry;

                KeDebugPrint("Added free block at %p with %zu pages\n",
                             (PVOID)start_address, page_count);
            }
        }
    }

    KeDebugPrint("Physical memory manager initialized\n");
}

KERNEL_API STATUS MmAllocatePage(PVOID* Block) {
    KiAcquireSpinlock(&slAllocatePage);
    if (!Block) {
        SetLastError(STATUS_INVALID_PARAMETER);
        KiReleaseSpinlock(&slAllocatePage);
        return STATUS_INVALID_PARAMETER;
    }

    PMM_FREELIST_ENTRY prev = NULL;
    PMM_FREELIST_ENTRY current = FreeListHead;

    while (current != NULL) {
        if (current->PageCount >= 1) {
            PVOID allocated_page = (PVOID)current;

            if (current->PageCount == 1) {
                // Remove the block from the list
                if (prev == NULL) {
                    FreeListHead = current->Next;
                } else {
                    prev->Next = current->Next;
                }
            } else {
                // Split the block: move header to next page
                PMM_FREELIST_ENTRY new_entry =
                    (PMM_FREELIST_ENTRY)((PUCHAR)current + PAGE_SIZE);
                new_entry->PageCount = current->PageCount - 1;
                new_entry->Next = current->Next;

                if (prev == NULL) {
                    FreeListHead = new_entry;
                } else {
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

KERNEL_API void MmFreePage(PVOID Block) {
    if (!Block) {
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

KERNEL_API ULONGLONG MmGetHighestPhysicalAddress() {
    SIZE_T dEntryCount = MmGetMemoryMapEntryCount();
    struct KMEMORY_MAP_ENTRY ent;
    ULONGLONG ullHighestAddress = 0;

    for (SIZE_T i = 0; i < dEntryCount; i++) {
        STATUS status = MmGetMemoryMapEntry(&ent, i);
        if (status != STATUS_SUCCESS) {
            KeDebugPrint("Failure retrieving entry %zu.\n", i);
            SetLastError(STATUS_NOT_FOUND);
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }

        if (ent.Base + ent.Length > ullHighestAddress) {
            ullHighestAddress = ent.Base + ent.Length;
        }
    }

    return ullHighestAddress;
}