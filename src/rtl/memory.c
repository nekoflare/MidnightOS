//
// Created by Neko on 06.03.2025.
//

#include "memory.h"

#include <string.h>
#include <ke/bugcheck.h>

#include "dlmalloc.h"

PVOID RtlZeroMallocSafe(
    SIZE_T Size) {
    PVOID Data = malloc(Size);
    if (!Data) {
        // TODO: Get memory back from users, e.g: page them out and get it back for our own use.
        KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        __builtin_unreachable();
    }

    memset(Data, 0, Size);

    return Data;
}
