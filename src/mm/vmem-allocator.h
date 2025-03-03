//
// Created by Neko on 02.03.2025.
//

#ifndef VMEM_ALLOCATOR_H
#define VMEM_ALLOCATOR_H

#include <kernel.h>

KERNEL_API STATUS MmAllocateKernelVirtualMemory(
    PULONGLONG Address,
    SIZE_T Length);

KERNEL_API void MiInitializeVirtualMemoryAllocator();

#endif //VMEM_ALLOCATOR_H
