//
// Created by Neko on 01.03.2025.
//

#include <rtl/limine.h>

#include "common.h"

#include <ke/bugcheck.h>
#include <ke/error.h>

volatile struct limine_hhdm_request hhdmRequest = {.id = LIMINE_HHDM_REQUEST, .revision = 0, .response = NULL};

KERNEL_API ULONGLONG MmGetMemoryOffset() {
    if (!hhdmRequest.response) {
        KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
    }

    SetLastError(STATUS_FAILURE);
    return hhdmRequest.response->offset;
}