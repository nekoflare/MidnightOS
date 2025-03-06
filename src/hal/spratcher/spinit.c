/*
File Creator: AzureianGH
File Name: spinit.c

Desc:
This is the main C file for most SPRATCHER components.
*/

#include <ke/stacktrace.h>
#include <ke/irql.h>
#include <kdbg/debug_print.h>
#include <cpu/cpu.h>
#include <cpuid.h>
#include <ke/bugcheck.h>
#include <hal/idt/idt.h>
#include <hal/initialize_arch.h>
#include <mm/physical.h>
#include <mm/virtual.h>
#include <mm/vmem-allocator.h>
#include <rtl/dlmalloc.h>
#include <rtl/runtime.h>

#include "features.h"

CHAR* SpratcherCurrentStep = {0};

// Forward declarations
STATUS KiSpratcherInitStage0(void);

KERNEL_API void KiSpratcherInit()
{
    PREVENT_DOUBLE_INIT
    KIRQL OldIrql;
    BOOL IrqlSet = FALSE;
    if (KeGetCurrentIrql() < HIGH_LEVEL) {
        KeRaiseIrql(HIGH_LEVEL, &OldIrql);
        IrqlSet = TRUE;
    }

    const STATUS dStatus = KiSpratcherInitStage0();

    if (IrqlSet)
        KeLowerIrql(OldIrql);

    if (dStatus != STATUS_SUCCESS) {
        KeDebugPrint("Spratcher failed to initialize\n");
        KeBugCheck(BUGCHECK_UNEXPECTED_STATE);
    }

    KeDebugPrint("Spratcher initialized\n");
}

#define SPRATCHER_ASSERT(x, y, z) if (!(x)) { KeDebugPrint("Spratcher: %s\n", y); } else { KeDebugPrint("Spratcher: %s\n", z); }

void KiPrintSupportedCPUExtension(BOOL Exists, LPSTR Extension) {
    if (Exists)
        KeDebugPrint("%s is supported\n", Extension);
}

void KiPrintSupportedCpuExtensionAndEnable(
    BOOL Exists,
    LPSTR Extension,
    void(*EnableFunction)()) {
    if (Exists) {
        KiPrintSupportedCPUExtension(TRUE, Extension);
        EnableFunction();
    }
}

STATUS KiSpratcherInitStage0(void) {
    PREVENT_DOUBLE_INIT
    KeDebugPrint("Spratcher Build [%s, %s]\n", __DATE__, __TIME__);
    // -------------------------------------------------------------------------------- //
    KiInitializeHAL();
    // -------------------------------------------------------------------------------- //
    KeDebugPrint("[ Done ] CPU setup complete\n");
    // -------------------------------------------------------------------------------- //
    KiInitializePhysicalMemoryManager();
    MiInitializeVirtualMemoryAllocator();
    MiInitializeVirtualMemory();
    MiInitializeKernelHeap();
    KiDLMallocInitialize();
    KeDebugPrint("[ Done ] Memory manager initialized\n");
    // -------------------------------------------------------------------------------- //
    KiStackTraceInit();
    KeStackTraceRegDefaults();
    KeDebugPrint("[ Done ] Stack frame prepared\n");
    // -------------------------------------------------------------------------------- //

    UINT Eax, Ebx, Ecx, Edx;

    // CPUID(0): Get highest function supported
    __get_cpuid(0, &Eax, &Ebx, &Ecx, &Edx);
    if (Eax < 1) {
        SPRATCHER_ASSERT(0, "CPUID function 1 not supported", ""); // Hard fail
        KeBugCheck(BUGCHECK_UNEXPECTED_STATE);
        __builtin_unreachable();
    }

    // CPUID(1): Get processor features
    __get_cpuid(1, &Eax, &Ebx, &Ecx, &Edx);

    // Correct feature checks
    KiPrintSupportedCPUExtension(Edx & (1 << 4),  "TSC is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 5),  "MSR is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 8),  "CMOV is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 11), "SYSCALL is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 19), "SSE is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 26), "SSE2 is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 0),  "SSE3 is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 9),  "SSSE3 is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 12), "FMA is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 19), "SSE4.1 is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 20), "SSE4.2 is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 23), "POPCNT is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 25), "AES is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 30), "RDRAND is supported");
    KiPrintSupportedCpuExtensionAndEnable(Ecx & (1 << 28), "AVX is supported", &KiEnableAVX);

    // CPUID(0x80000001): Extended Features
    if (Eax >= 0x80000001) {
        __get_cpuid(0x80000001, &Eax, &Ebx, &Ecx, &Edx);
        KiPrintSupportedCPUExtension(Edx & (1 << 29), "NX is supported");
        KiPrintSupportedCPUExtension(Ecx & (1 << 0),  "F16C is supported");
        KiPrintSupportedCPUExtension(Edx & (1 << 23), "MMX is supported");
        KiPrintSupportedCPUExtension(Edx & (1 << 31), "3DNow! is supported");

    }

    KiPrintSupportedCPUExtension(Ebx & (1 << 28), "Hyper-Threading is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 5),  "Intel VT-x is supported");
    KiPrintSupportedCPUExtension(Ecx & (1 << 2),  "AMD SVM is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 20), "Execute Disable (XD) is supported");
    KiPrintSupportedCPUExtension(Ebx & (1 << 38), "Turbo Boost is supported");
    KiPrintSupportedCPUExtension(Edx & (1 << 0),  "FPU is supported");

    KeDebugPrint("[ Done ] Spratcher is now exiting...\n");

    return STATUS_SUCCESS; // for now, everything is just successful, we will add more checks later.
}
