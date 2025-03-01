//
// Created by Neko on 28.02.2025.
//

#include "irql.h"

#include <cpu/cpu.h>

#include "bugcheck.h"

KIRQL CurrentIrql = HIGH_LEVEL; // by default, it will be high level.

KERNEL_API LPSTR StringifyIrql(
    KIRQL Irql) {
    switch (Irql) {
        case PASSIVE_LEVEL: return "PASSIVE_LEVEL";
        case APC_LEVEL: return "APC_LEVEL";
        case DISPATCH_LEVEL: return "DISPATCH_LEVEL";
        case DEVICE_LEVEL: return "DEVICE_LEVEL";
        case HIGH_LEVEL: return "HIGH_LEVEL";
        default: return "UNKNOWN_LEVEL (Literally)";
    }
}

/* change kernel states */
KERNEL_API void KiTransitionIrql() {
    switch (CurrentIrql) {
        case HIGH_LEVEL:
            KiExplicitDisableInterrupts();
            break;
        default:
            KiExplicitEnableInterrupts();
            break;
    }
}

KERNEL_API void KeRaiseIrql(
    KIRQL NewIrql,
    PKIRQL OldIrql
) {
    if (OldIrql != NULL)
        *OldIrql = CurrentIrql;

    if (CurrentIrql >= NewIrql) {
        KeBugCheck(BUGCHECK_IRQL_LESS_OR_EQUAL);
    }

    CurrentIrql = NewIrql;
    KiTransitionIrql();
}

KERNEL_API KIRQL KeGetCurrentIrql() {
    return CurrentIrql;
}

KERNEL_API void KeLowerIrql(
    KIRQL OldIrql) {
    CurrentIrql = OldIrql;
}