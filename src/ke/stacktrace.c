/*
File Creator: AzureianGH
File Name: stacktrace.c

Desc:
This is the main C file for the stacktrace component.
*/
#include "stacktrace.h"
#include <kdbg/debug_print.h>
#include <ke/spratcher/spinit.h>
#include <rtl/spinlock.h>

static struct SPINLOCK slStackTrace;
ULONGLONG FunctionAddress[25] = {0};
CHAR* FunctionName[25] = {0};
extern void KernelMain(void);

KERNEL_API void KeStackTraceInit() {
    RtlCreateSpinLock(&slStackTrace);
}
void KeStackTraceRegisterFunction(ULONGLONG address, CHAR* name) {
    for (UINT i = 0; i < 25; i++) {
        if (FunctionAddress[i] == 0) {
            FunctionAddress[i] = address;
            FunctionName[i] = name;
            break;
        }
    }

}

KERNEL_API CHAR* KeStackTraceGetFunctionName(ULONGLONG address) {

    for (UINT i = 0; i < 25; i++) {
        if (FunctionAddress[i] == address) {

            return FunctionName[i];
        }
    }

    return "Private function";
}

KERNEL_API void KeStackTraceRegDefaults() {
    KeDebugPrint("Registering default functions...\n");
    KeStackTraceRegisterFunction((ULONGLONG)KeWalkStack, "KeWalkStack");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceRegisterFunction, "KeStackTraceRegisterFunction");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceGetFunctionName, "KeStackTraceGetFunctionName");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceRegDefaults, "KeStackTraceRegDefaults");
    KeStackTraceRegisterFunction((ULONGLONG)KeDebugPrint, "KeDebugPrint");
    KeStackTraceRegisterFunction((ULONGLONG)KernelMain, "KernelMain");
    KeStackTraceRegisterFunction((ULONGLONG)KiSpratcherInit, "KiSpratcherInit");
    KeDebugPrint("Done registering default functions\n");
}

KERNEL_API void KeWalkStackPre(PVOID stack_top, UINT max_frames, ULONGLONG *addresses) {

    ULONGLONG* base_pointer = (ULONGLONG*)stack_top;
    for (UINT i = 0; i < max_frames; i++) {
        if (base_pointer == NULL) {
            break; // stop if we reach the end of the stack
        }

        ULONGLONG return_address = base_pointer[1]; // get return address from the next address in the stack frame
        addresses[i] = return_address; // store the return address in the array

        base_pointer = (ULONGLONG*)base_pointer[0]; // move to the previous stack frame (previous base pointer)
    }
}

// check if the instruction at the given address is a CALL
KERNEL_API ULONGLONG KeGetCallTarget(ULONGLONG return_address) {
    UCHAR* instruction = (UCHAR*)(return_address - 5); // assume rel32 CALL first

    // relative CALL instruction
    if (instruction[0] == 0xE8) {
        INT rel_offset = *(INT*)(instruction + 1); // 32-bit relative offset
        return return_address + rel_offset; // function address
    }

    return 0; // not a CALL instruction
}

KERNEL_API void KeWalkStack(UINT max_frames) {
    RtlAcquireSpinlock(&slStackTrace);
    ULONGLONG addresses[max_frames];
    ULONGLONG* stack_top;

    asm volatile ("mov %%rbp, %0" : "=r"(stack_top));

    KeDebugPrint("BEGIN [STACK TRACE]\n");

    KeWalkStackPre(stack_top, max_frames, addresses);
    for (UINT frame = 0; frame < max_frames; frame++) {
        if (addresses[frame] == 0) break;
        
        ULONGLONG function_address = KeGetCallTarget(addresses[frame]);

        CHAR* function_name = KeStackTraceGetFunctionName(function_address);

        //test all things before printing to make sure not null
        if (function_address == NULL || function_name == NULL || addresses[frame] == NULL) {
            break;
        }

        KeDebugPrint("%s (0x%x%x) RETURN AT 0x%x%x\n", function_name, (UINT)(function_address >> 32), (UINT)(function_address & 0xFFFFFFFF), (UINT)(addresses[frame] >> 32), (UINT)(addresses[frame] & 0xFFFFFFFF));
    }

    KeDebugPrint("END [STACK TRACE]\n");
    RtlReleaseSpinlock(&slStackTrace);
}
