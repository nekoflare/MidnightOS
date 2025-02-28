//
// Created by Neko on 28.02.2025.
//

#include "bugcheck.h"

#include <cpu/cpu.h>
#include <kdbg/debug_print.h>

KERNEL_API LPSTR StringifyBugCheckError(BUGCHECK_REASON BugCheckReason) {
    switch (BugCheckReason) {
        case IRQL_LESS_OR_EQUAL: return "IRQL_LESS_OR_EQUAL";
        default: return "Unkown bug check reason.";
    }
}

KERNEL_API void KeBugCheck(BUGCHECK_REASON BugCheckReason) {
    KeDebugPrintNoSync("*** STOP ***\n");
    KeDebugPrintNoSync("STATUS: %s", StringifyBugCheckError(BugCheckReason));
    asm volatile ("xchg %bx, %bx");
    KiExplicitDisableInterrupts();
    KiExplicitHalt();
}