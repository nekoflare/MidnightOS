//
// Created by Neko on 28.02.2025.
//

#include "bugcheck.h"

#include <cpu/cpu.h>
#include <kdbg/debug_print.h>
#include <ke/stacktrace.h>

KERNEL_API LPSTR StringifyBugCheckError(BUGCHECK_REASON BugCheckReason) {
    switch (BugCheckReason) {
        case BUGCHECK_IRQL_LESS_OR_EQUAL: return "IRQL_LESS_OR_EQUAL";
        case BUGCHECK_UNEXPECTED_STATE: return "UNEXPECTED_STATE";
        case BUGCHECK_UNRECOVERABLE_NO_MEMORY: return "UNRECOVERABLE_NO_MEMORY";
        case BUGCHECK_UNEXPECTED_INTERRUPT: return "UNEXPECTED_INTERRUPT";
        default: return "Unkown bug check reason.";
    }
}

KERNEL_API void KeBugCheck(BUGCHECK_REASON BugCheckReason) {
    KeDebugPrintNoSync("*** BEGIN FATAL ***\n");
    KeWalkStack(256);
    KeDebugPrintNoSync("STATUS: %s\n", StringifyBugCheckError(BugCheckReason));
    KeDebugPrintNoSync("***    STOP     ***\n");
    
    KiExplicitDisableInterrupts();
    KiExplicitHalt();
}