//
// Created by Neko on 01.03.2025.
//

#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <kernel.h>

enum KMEMORY_MAP_ENTRY_TYPE
{
    MMET_USABLE,
    MMET_RESERVED,
    MMET_ACPI_RECLAIMABLE,
    MMET_ACPI_NVS,
    MMET_BAD_MEMORY,
    MMET_BOOTLOADER_RECLAIMABLE,
    MMET_KERNEL_AND_MODULES,
    MMET_FRAMEBUFFER
};

struct KMEMORY_MAP_ENTRY
{
    ULONGLONG Base;
    ULONGLONG Length;
    enum KMEMORY_MAP_ENTRY_TYPE Type;
};

typedef struct KMEMORY_MAP_ENTRY *PKMEMORY_MAP_ENTRY;

KERNEL_API LPSTR StringifyMemoryMapEntryType(enum KMEMORY_MAP_ENTRY_TYPE Type);

KERNEL_API SIZE_T MmGetMemoryMapEntryCount();
KERNEL_API STATUS MmGetMemoryMapEntry(PKMEMORY_MAP_ENTRY Entry, SIZE_T Index);

KERNEL_API void MmSummarizeMemoryMap();

KERNEL_API void KiInitializePhysicalMemoryManager();
KERNEL_API STATUS MmAllocatePage(PVOID *Page);
KERNEL_API void MmFreePage(PVOID Page);
KERNEL_API ULONGLONG MmGetHighestPhysicalAddress();

#endif // PHYSICAL_H
