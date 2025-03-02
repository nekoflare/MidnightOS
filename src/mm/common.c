//
// Created by Neko on 01.03.2025.
//

#include <rtl/limine.h>

#include "common.h"

#include <ke/bugcheck.h>
#include <ke/error.h>

volatile struct limine_hhdm_request hhdmRequest = {.id = LIMINE_HHDM_REQUEST, .revision = 0, .response = NULL};

volatile struct limine_kernel_address_request kernelAddressRequest = { .id = LIMINE_KERNEL_ADDRESS_REQUEST, .revision = 0, .response = NULL};

KERNEL_API ULONGLONG MmGetMemoryOffset() {
    if (!hhdmRequest.response) {
        KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
    }

    SetLastError(STATUS_SUCCESS);
    return hhdmRequest.response->offset;
}

KERNEL_API ULONGLONG MmGetKernelAddressVirtual() {
    if (!kernelAddressRequest.response) {
        KeBugCheck(BUGCHECK_UNEXPECTED_STATE);
    }

    SetLastError(STATUS_SUCCESS);
    return kernelAddressRequest.response->virtual_base;
}