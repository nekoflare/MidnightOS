/*
File Creator: AzureianGH
File Name: stacktrace.c

Desc:
This is the main C file for the stacktrace component.
*/
#include "stacktrace.h"
#include <kdbg/debug_print.h>
#include <hal/spratcher/spinit.h>
#include <rtl/spinlock.h>
#include <hal/idt/idt.h>
#include <mm/physical.h>
#include <ke/bugcheck.h>
#include <ke/irql.h>
#include <ke/error.h>
#include <hal/initialize_arch.h>
#include <hal/io.h>
#include <cpu/cpu.h>
#include <cpuid.h>
#include <string.h>
#include <mm/common.h>
#include <rtl/dlmalloc.h>


static struct KSPINLOCK slStackTrace;
#define NumberOfFunctions 50
ULONGLONG FunctionAddress[NumberOfFunctions] = {0};
CHAR* FunctionName[NumberOfFunctions] = {0};
extern void KernelMain(void);
extern void KiInterruptHandler(INTERRUPT_STACK_FRAME* frame);
extern void KiISRCommonHandler();
extern STATUS KiSpratcherInitStage0();
extern void* sbrk(intptr_t increment);

KERNEL_API void KiStackTraceInit() {
    PREVENT_DOUBLE_INIT
    KiCreateSpinLock(&slStackTrace);
}
void KeStackTraceRegisterFunction(ULONGLONG address, CHAR* name) {
    for (UINT i = 0; i < NumberOfFunctions; i++) {
        if (FunctionAddress[i] == 0) {
            FunctionAddress[i] = address;
            FunctionName[i] = name;
            break;
        }
    }
}

KERNEL_API CHAR* KeStackTraceGetFunctionName(ULONGLONG address) {

    for (UINT i = 0; i < NumberOfFunctions; i++) {
        if (FunctionAddress[i] == address) {
            return FunctionName[i];
        }
    }

    return "Inlined function";
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

BOOL isInterruptHandler = FALSE;

KERNEL_API void KeWalkStack(UINT max_frames) {
    KiAcquireSpinlock(&slStackTrace);
    ULONGLONG addresses[max_frames];
    ULONGLONG* stack_top;

    asm volatile ("mov %%rbp, %0" : "=r"(stack_top));

    KeDebugPrint("BEGIN [STACK TRACE]\n\n");

    KeWalkStackPre(stack_top, max_frames, addresses);
    UINT longest_name_length = 0;
    for (UINT frame = 0; frame < max_frames; frame++) {
        if (addresses[frame] == 0) break;
        
        ULONGLONG function_address = KeGetCallTarget(addresses[frame]);
        CHAR* function_name = KeStackTraceGetFunctionName(function_address);

        if (function_name != NULL) {
            UINT name_length = strlen(function_name);
            if (name_length > longest_name_length) {
                longest_name_length = name_length;
            }
        }
    }

    for (UINT frame = 0; frame < max_frames; frame++) {
        if (addresses[frame] == 0) break;
        
        ULONGLONG function_address = KeGetCallTarget(addresses[frame]);
        CHAR* function_name = KeStackTraceGetFunctionName(function_address);

        if (function_address == NULL || function_name == NULL || addresses[frame] == NULL) {
            break;
        }

        if (isInterruptHandler == TRUE) {
            KeDebugPrint("(Possible Cause) %-*s RETURN AT 0x%x%x\n", longest_name_length, function_name, (UINT)(addresses[frame] >> 32), (UINT)(addresses[frame] & 0xFFFFFFFF));
            isInterruptHandler = FALSE;
            continue;
        }

        if (function_address == (ULONGLONG)KiInterruptHandler) {
            isInterruptHandler = TRUE;
        }
        KeDebugPrint("                 %-*s RETURN AT 0x%x%x\n", longest_name_length, function_name, (UINT)(addresses[frame] >> 32), (UINT)(addresses[frame] & 0xFFFFFFFF));
    }

    KeDebugPrint("\nEND [STACK TRACE]\n");
    KiReleaseSpinlock(&slStackTrace);
}


KERNEL_API void KeStackTraceRegDefaults() {

    /*
    ####################################################################################
    # NOTE: If you are registering a new function, INLINE FUNCTIONS ARE NOT SUPPORTED. #
    ####################################################################################
    */

    PREVENT_DOUBLE_INIT

    KeDebugPrint("Registering default functions...\n");
    KeStackTraceRegisterFunction((ULONGLONG)KeWalkStack, "KeWalkStack");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceRegisterFunction, "KeStackTraceRegisterFunction");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceGetFunctionName, "KeStackTraceGetFunctionName");
    KeStackTraceRegisterFunction((ULONGLONG)KeStackTraceRegDefaults, "KeStackTraceRegDefaults");
    KeStackTraceRegisterFunction((ULONGLONG)KeDebugPrint, "KeDebugPrint");
    KeStackTraceRegisterFunction((ULONGLONG)KernelMain, "KernelMain");
    KeStackTraceRegisterFunction((ULONGLONG)KiSpratcherInit, "KiSpratcherInit");
    KeStackTraceRegisterFunction((ULONGLONG)KiSpratcherInitStage0, "KiSpratcherInitStage0");
    KeStackTraceRegisterFunction((ULONGLONG)KiInterruptHandler, "KiInterruptHandler");
    KeStackTraceRegisterFunction((ULONGLONG)KiISRCommonHandler, "KiISRCommonHandler");
    KeStackTraceRegisterFunction((ULONGLONG)KiInitializeHAL, "KiInitializeHAL");
    KeStackTraceRegisterFunction((ULONGLONG)KiInitializePhysicalMemoryManager, "KiInitializePhysicalMemoryManager");
    KeStackTraceRegisterFunction((ULONGLONG)KeRaiseIrql, "KeRaiseIrql");
    KeStackTraceRegisterFunction((ULONGLONG)KeLowerIrql, "KeLowerIrql");
    KeStackTraceRegisterFunction((ULONGLONG)KeBugCheck, "KeBugCheck");
    KeStackTraceRegisterFunction((ULONGLONG)KiPrintRegisters, "KiPrintRegisters");
    KeStackTraceRegisterFunction((ULONGLONG)KiExplicitHalt, "KiExplicitHalt");
    KeStackTraceRegisterFunction((ULONGLONG)KiCreatePortResource, "IoCreatePortResource");
    KeStackTraceRegisterFunction((ULONGLONG)KiWritePortByte, "IoWritePortByte");
    KeStackTraceRegisterFunction((ULONGLONG)KiDestroyPortResource, "IoDestroyPortResource");
    KeStackTraceRegisterFunction((ULONGLONG)KiInitializeDebugPort, "KiInitializeDebugConn");
    KeStackTraceRegisterFunction((ULONGLONG)KeLowerIrql, "KeLowerIrql");
    KeStackTraceRegisterFunction((ULONGLONG)KeGetCurrentIrql, "KeGetCurrentIrql");
    KeStackTraceRegisterFunction((ULONGLONG)KeDebugPrint, "KeDebugPrint");
    KeStackTraceRegisterFunction((ULONGLONG)KeBugCheck, "KeBugCheck");
    KeStackTraceRegisterFunction((ULONGLONG)KeWalkStackPre, "KeWalkStackPre");
    KeStackTraceRegisterFunction((ULONGLONG)KeGetCallTarget, "KeGetCallTarget");
    KeStackTraceRegisterFunction((ULONGLONG)KeGetCpuName, "KeGetCpuName");
    KeStackTraceRegisterFunction((ULONGLONG)KeGetCpuVendorRaw, "KeGetCpuVendorRaw");
    KeStackTraceRegisterFunction((ULONGLONG)MmGetMemoryOffset, "MmGetMemoryOffset");
    KeStackTraceRegisterFunction((ULONGLONG)MmGetMemoryMapEntryCount, "MmGetMemoryMapEntryCount");
    KeStackTraceRegisterFunction((ULONGLONG)MmGetMemoryMapEntry, "MmGetMemoryMapEntry");
    KeStackTraceRegisterFunction((ULONGLONG)MmSummarizeMemoryMap, "MmSummarizeMemoryMap");
    KeStackTraceRegisterFunction((ULONGLONG)malloc, "malloc");
    KeStackTraceRegisterFunction((ULONGLONG)realloc, "realloc");
    KeStackTraceRegisterFunction((ULONGLONG)calloc, "calloc");
    KeStackTraceRegisterFunction((ULONGLONG)free, "free");
    KeStackTraceRegisterFunction((ULONGLONG)memalign, "memalign");
    KeStackTraceRegisterFunction((ULONGLONG)valloc, "valloc");
    KeStackTraceRegisterFunction((ULONGLONG)pvalloc, "pvalloc");
    KeStackTraceRegisterFunction((ULONGLONG)cfree, "cfree");
    KeStackTraceRegisterFunction((ULONGLONG)independent_comalloc, "independent_comalloc");
    KeStackTraceRegisterFunction((ULONGLONG)sbrk, "sbrk");

    KeDebugPrint("Done registering default functions\n");
}