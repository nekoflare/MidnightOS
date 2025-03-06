/*
File Creator: AzureianGH
File Name: stacktrace.c

Desc:
This is the main C file for the stacktrace component.
*/
#include "stacktrace.h"
#include <cpu/cpu.h>
#include <cpuid.h>
#include <hal/idt/idt.h>
#include <hal/initialize_arch.h>
#include <hal/io.h>
#include <hal/spratcher/spinit.h>
#include <kdbg/debug_print.h>
#include <ke/bugcheck.h>
#include <ke/error.h>
#include <ke/irql.h>
#include <mm/common.h>
#include <mm/physical.h>
#include <rtl/dlmalloc.h>
#include <rtl/spinlock.h>
#include <string.h>

static struct KSPINLOCK slStackTrace;
#define NumberOfFunctions 50
ULONGLONG FunctionAddress[NumberOfFunctions] = {0};
CHAR *FunctionName[NumberOfFunctions] = {0};
extern void KernelMain(void);
extern void KiInterruptHandler(INTERRUPT_STACK_FRAME *frame);
extern void KiISRCommonHandler();
extern STATUS KiSpratcherInitStage0();
extern void *sbrk(intptr_t increment);

KERNEL_API void KiStackTraceInit()
{
    PREVENT_DOUBLE_INIT
    KiCreateSpinLock(&slStackTrace);
}

void KeStackTraceRegisterFunction(ULONGLONG address, CHAR *name)
{
    for (UINT i = 0; i < NumberOfFunctions; i++)
    {
        if (FunctionAddress[i] == 0)
        {
            FunctionAddress[i] = address;
            FunctionName[i] = name;
            break;
        }
    }
}

KERNEL_API CHAR *KeStackTraceGetFunctionName(ULONGLONG address)
{

    for (UINT i = 0; i < NumberOfFunctions; i++)
    {
        if (FunctionAddress[i] == address)
        {
            return FunctionName[i];
        }
    }

    return "Inlined function";
}

KERNEL_API void KeWalkStackPre(PVOID stack_top, UINT max_frames, ULONGLONG *Addresses)
{
    ULONGLONG *BasePointer = stack_top;
    for (UINT i = 0; i < max_frames; i++)
    {
        if (BasePointer == NULL)
        {
            break; // stop if we reach the end of the stack
        }

        ULONGLONG ReturnAddress = BasePointer[1]; // get return address from the next address in the stack frame
        Addresses[i] = ReturnAddress;             // store the return address in the array

        BasePointer = (ULONGLONG *)BasePointer[0]; // move to the previous stack frame (previous base pointer)
    }
}

// check if the instruction at the given address is a CALL
KERNEL_API ULONGLONG KeGetCallTarget(ULONGLONG return_address)
{
    UCHAR *Instruction = (UCHAR *)(return_address - 5); // assume rel32 CALL first

    // relative CALL instruction
    if (Instruction[0] == 0xE8)
    {
        INT RelOffset = *(INT *)(Instruction + 1); // 32-bit relative offset
        return return_address + RelOffset;         // function address
    }

    return 0; // not a CALL instruction
}

BOOL IsInterruptHandler = FALSE;

KERNEL_API void KeWalkStack(UINT MAX_FRAMES)
{
    KiAcquireSpinlock(&slStackTrace);
    ULONGLONG Addresses[MAX_FRAMES];
    ULONGLONG *StackTop;

    asm volatile("mov %%rbp, %0" : "=r"(StackTop));

    KeDebugPrint("BEGIN [STACK TRACE]\n\n");

    KeWalkStackPre(StackTop, MAX_FRAMES, Addresses);
    UINT LongestNameLength = 0;
    for (UINT FrameIndex = 0; FrameIndex < MAX_FRAMES; FrameIndex++)
    {
        if (Addresses[FrameIndex] == 0)
            break;

        ULONGLONG FunctionAddress = KeGetCallTarget(Addresses[FrameIndex]);
        CHAR *FunctionName = KeStackTraceGetFunctionName(FunctionAddress);

        if (FunctionName != NULL)
        {
            UINT NameLength = strlen(FunctionName);
            if (NameLength > LongestNameLength)
            {
                LongestNameLength = NameLength;
            }
        }
    }

    for (UINT FrameIndex = 0; FrameIndex < MAX_FRAMES; FrameIndex++)
    {
        if (Addresses[FrameIndex] == 0)
            break;

        ULONGLONG FunctionAddress = KeGetCallTarget(Addresses[FrameIndex]);
        CHAR *FunctionName = KeStackTraceGetFunctionName(FunctionAddress);

        if ((PVOID)FunctionAddress == NULL || FunctionName == NULL || (PVOID)Addresses[FrameIndex] == NULL)
        {
            break;
        }

        if (IsInterruptHandler == TRUE)
        {
            KeDebugPrint("(Possible Cause) %-*s RETURN AT 0x%x%x\n", LongestNameLength, FunctionName,
                         (UINT)(Addresses[FrameIndex] >> 32), (UINT)(Addresses[FrameIndex] & 0xFFFFFFFF));
            IsInterruptHandler = FALSE;
            continue;
        }

        if (FunctionAddress == (ULONGLONG)KiInterruptHandler)
        {
            IsInterruptHandler = TRUE;
        }
        KeDebugPrint("                 %-*s RETURN AT 0x%x%x\n", LongestNameLength, FunctionName,
                     (UINT)(Addresses[FrameIndex] >> 32), (UINT)(Addresses[FrameIndex] & 0xFFFFFFFF));
    }

    KeDebugPrint("\nEND [STACK TRACE]\n");
    KiReleaseSpinlock(&slStackTrace);
}

KERNEL_API void KeStackTraceRegDefaults()
{

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