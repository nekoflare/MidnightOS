//
// Created by Neko on 02.03.2025.
//

#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <kernel.h>
#include "paging.h"

struct VIRTUAL_MEMORY_DESCRIPTOR_ENTRY {
    ULONGLONG Base;
    ULONGLONG Length;
};

enum VM_SECURITY {
    VMS_NO_EXECUTE = 1 << 0,
    VMS_READ_WRITE = 1 << 1,
    VMS_SUPERVISOR = 1 << 2,
    VMS_USER       = 0,
};

enum VM_MI_PAGING_FLAGS {
    VMMIPF_PAGE_WRITE_THROUGH = 1 << 0,
    VMMIPF_PAGE_CACHE_DISABLE = 1 << 1,
    VMMIPF_PAGE_SIZE_FLAG     = 1 << 2,
};

typedef struct VIRTUAL_MEMORY_DESCRIPTOR_ENTRY* PVIRTUAL_MEMORY_DESCRIPTOR_ENTRY;

KERNEL_API void MiInitializeVirtualMemory();
KERNEL_API void MiGetKernelVirtualMemoryDescriptor(PVIRTUAL_MEMORY_DESCRIPTOR_ENTRY* Descriptor);
KERNEL_API void MiGetKernelPageMapAddressPhysical(PVOID* PageMap);
KERNEL_API void MiGetKernelPageMapAddressVirtual(PVOID* PageMap);
KERNEL_API STATUS MiMapPage(
    enum VM_SECURITY Security,
    enum VM_MI_PAGING_FLAGS PagingFlags,
    PVOID Physical,
    PVOID Virtual,
    PVOID Pagemap /* Side note: it must be virtual. its universal*/);
KERNEL_API STATUS MmInvalidatePages(PVOID Virtual, SIZE_T Length);

#endif //VIRTUAL_H
