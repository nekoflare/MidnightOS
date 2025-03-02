//
// Created by Neko on 01.03.2025.
//

#ifndef COMMON_H
#define COMMON_H

#include <kernel.h>

#define PAGE_SIZE 4096

KERNEL_API ULONGLONG MmGetMemoryOffset(); // Gives offset to get virtual address. HHDM
KERNEL_API ULONGLONG MmGetKernelAddressVirtual();

#endif //COMMON_H
