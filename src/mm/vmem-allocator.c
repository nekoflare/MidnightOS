//
// Created by Neko on 02.03.2025.
//

#include "vmem-allocator.h"

#include <ke/bugcheck.h>
#include <ke/error.h>
#include <rtl/spinlock.h>

#include "common.h"
#include "virtual.h"

struct KSPINLOCK slAllocateKernelVirtualMemory;

KERNEL_API void MiInitializeVirtualMemoryAllocator() {
    PREVENT_DOUBLE_INIT
    KiCreateSpinLock(&slAllocateKernelVirtualMemory); // initialize
}

KERNEL_API STATUS MmAllocateKernelVirtualMemory(
    PULONGLONG Address,
    SIZE_T Length) {
    if (Length % PAGE_SIZE != 0) {
        SetLastError(STATUS_INVALID_PARAMETER);
        return STATUS_INVALID_PARAMETER;
    }

    KiAcquireSpinlock(&slAllocateKernelVirtualMemory);
    //  Get the kernel VDA.
    PKVIRTUAL_MEMORY_DESCRIPTOR_ENTRY kernelVmde;
    MiGetKernelVirtualMemoryDescriptor(&kernelVmde);

    if (Length >= kernelVmde->Length) {
        SetLastError(STATUS_OUT_OF_MEMORY);
        return STATUS_OUT_OF_MEMORY;
    }

    ULONGLONG ullAllocatedMemory = kernelVmde->Base;
    kernelVmde->Base += Length;
    kernelVmde->Length -= Length;

    KiReleaseSpinlock(&slAllocateKernelVirtualMemory);

    *Address = ullAllocatedMemory;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}