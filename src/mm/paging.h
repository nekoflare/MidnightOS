//
// Created by Neko on 02.03.2025.
//

#ifndef PAGING_H
#define PAGING_H

#include <kernel.h>

enum VM_PAGING_FLAGS {
    VMPF_PRESENT = 1 << 0,
    VMPF_READ_WRITE = 1 << 1,
    VMPF_USER = 0,
    VMPF_SUPERVISOR = 1 << 2,
    VMPF_PAGE_WRITE_THROUGH = 1 << 3,
    VMPF_PAGE_CACHE_DISABLE = 1 << 4,
    VMPF_PAGE_SIZE = 1 << 7, // PML4 doesn't have this one.
    VMPF_NO_EXECUTE = 1ULL << 63
};

// physical address can be |='ed right in btw

#endif //PAGING_H
