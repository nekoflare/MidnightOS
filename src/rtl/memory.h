//
// Created by Neko on 06.03.2025.
//

#ifndef MEMORY_H
#define MEMORY_H

#include <kernel.h>

/* Safe means it will always give memory to the kernel. If theres absolutely no memory it will crash the system */
/* Allocate n-bytes and memset them to 0. */
KERNEL_API PVOID RtlZeroMallocSafe(
    SIZE_T Size);

#endif //MEMORY_H
