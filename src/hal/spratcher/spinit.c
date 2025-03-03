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
#include <rtl/dlmalloc.h>

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

STATUS KiSpratcherInitStage0(void) {
    KeDebugPrint("Spratcher is initializing...\n");
    KeDebugPrint("Spratcher Build [%s, %s]\n", __DATE__, __TIME__);
    KeDebugPrint("[ Init ] Spratcher is setting up CPU...\n");
    // -------------------------------------------------------------------------------- //
    KiInitializeHAL();
    // -------------------------------------------------------------------------------- //
    KeDebugPrint("[ Done ] CPU setup complete\n");
    // -------------------------------------------------------------------------------- //
    KeDebugPrint("[ Init ] Spratcher is initializing memory...\n");
    KiInitializePhysicalMemoryManager();
    KiDLMallocInitialize();
    KeDebugPrint("[ Done ] Memory manager initialized\n");
    // -------------------------------------------------------------------------------- //
    KeDebugPrint("[ Init ] Spratcher is preparing stack frame...\n");
    KiStackTraceInit();
    KeStackTraceRegDefaults();
    KeDebugPrint("[ Done ] Stack frame prepared\n");
    // -------------------------------------------------------------------------------- //

    KeDebugPrint("[ Init ] Spratcher is testing extended CPU features...\n");

    UINT Eax, Ebx, Ecx, Edx;

    // CPUID(0): Get highest function supported
    __get_cpuid(0, &Eax, &Ebx, &Ecx, &Edx);
    if (Eax < 1) {
        SPRATCHER_ASSERT(0, "CPUID function 1 not supported", ""); // Hard fail
        return STATUS_NOT_SUPPORTED;
    }

    // CPUID(1): Get processor features
    __get_cpuid(1, &Eax, &Ebx, &Ecx, &Edx);

    // Correct feature checks
    SPRATCHER_ASSERT(Edx & (1 << 4), "TSC is not supported", "TSC is supported");
    SPRATCHER_ASSERT(Edx & (1 << 5), "MSR is not supported", "MSR is supported");
    SPRATCHER_ASSERT(Edx & (1 << 8), "CMOV is not supported", "CMOV is supported");
    SPRATCHER_ASSERT(Edx & (1 << 11), "SYSCALL is not supported", "SYSCALL is supported");
    SPRATCHER_ASSERT(Edx & (1 << 19), "SSE is not supported", "SSE is supported");
    SPRATCHER_ASSERT(Edx & (1 << 26), "SSE2 is not supported", "SSE2 is supported");

    SPRATCHER_ASSERT(Ecx & (1 << 0), "SSE3 is not supported", "SSE3 is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 9), "SSSE3 is not supported", "SSSE3 is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 12), "FMA is not supported", "FMA is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 19), "SSE4.1 is not supported", "SSE4.1 is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 20), "SSE4.2 is not supported", "SSE4.2 is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 23), "POPCNT is not supported", "POPCNT is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 25), "AES is not supported", "AES is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 28), "AVX is not supported", "AVX is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 30), "RDRAND is not supported", "RDRAND is supported");

    // CPUID(0x80000001): Extended Features
    if (Eax >= 0x80000001) {
        __get_cpuid(0x80000001, &Eax, &Ebx, &Ecx, &Edx);
        SPRATCHER_ASSERT(Edx & (1 << 29), "NX is not supported", "NX is supported");
        SPRATCHER_ASSERT(Ecx & (1 << 0), "F16C is not supported", "F16C is supported");
        SPRATCHER_ASSERT(Edx & (1 << 23), "MMX is not supported", "MMX is supported");
        SPRATCHER_ASSERT(Edx & (1 << 31), "3DNow! is not supported", "3DNow! is supported");

    }

    SPRATCHER_ASSERT(Ebx & (1 << 28), "Hyper-Threading is not supported", "Hyper-Threading is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 5), "Intel VT-x is not supported", "Intel VT-x is supported");
    SPRATCHER_ASSERT(Ecx & (1 << 2), "AMD SVM is not supported", "AMD SVM is supported");
    SPRATCHER_ASSERT(Edx & (1 << 20), "Execute Disable (XD) is not supported", "Execute Disable (XD) is supported");
    SPRATCHER_ASSERT(Ebx & (1 << 38), "Turbo Boost is not supported", "Turbo Boost is supported");
    SPRATCHER_ASSERT(Edx & (1 << 0), "FPU is not supported", "FPU is supported");

    SpratcherCurrentStep = "Test FPOps";
    FLOAT TestFloat1 = 1.0f;
    FLOAT TestFloat2 = 2.0f;
    FLOAT TestFloat3 = TestFloat1 + TestFloat2;
    SPRATCHER_ASSERT(TestFloat3 == 3.0f, "Floating point operations are not supported", "Floating point operations are supported");

    KeDebugPrint("[ Done ] CPUID tests completed\n");
    KeDebugPrint("[ Done ] Stage 0 Complete.\n");
    KeDebugPrint("[ KILL ] Spratcher is now exiting...\n");

    return STATUS_SUCCESS; // for now, everything is just successful, we will add more checks later.
}
