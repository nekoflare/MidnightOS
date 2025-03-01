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

#define SPRATCHER_ASSERT(x, y, z) if (!(x)) { KeDebugPrint("\033[31mSpratcher: %s\033[0m\n", y); } else { KeDebugPrint("Spratcher: %s\n", z); }

CHAR* SpratcherCurrentStep = {0};

int KiSpratcherInitStage0(void);

KERNEL_API int KiSpratcherInit()
{
    if (KeGetCurrentIrql() < HIGH_LEVEL) KeRaiseIrql(HIGH_LEVEL, NULL);
    return KiSpratcherInitStage0();
}



#include <cpuid.h>

#define SPRATCHER_ASSERT(x, y, z) if (!(x)) { KeDebugPrint("Spratcher: %s\n", y); } else { KeDebugPrint("Spratcher: %s\n", z); }

int KiSpratcherInitStage0(void) {
    KeDebugPrint("Spratcher Init...\n");
    KeDebugPrint("Spratcher Build [%s, %s]\n", __DATE__, __TIME__);
    KeDebugPrint("[ Init ] Spratcher is preparing stack frame...\n");
    KeStackTraceInit();
    KeStackTraceRegDefaults();
    KeDebugPrint("[ Init ] Spratcher is testing extended CPU features...\n");

    UINT eax, ebx, ecx, edx;

    // CPUID(0): Get highest function supported
    __get_cpuid(0, &eax, &ebx, &ecx, &edx);
    if (eax < 1) {
        SPRATCHER_ASSERT(0, "CPUID function 1 not supported", ""); // Hard fail
        return STATUS_NOT_SUPPORTED;
    }

    // CPUID(1): Get processor features
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);

    // Correct feature checks
    SPRATCHER_ASSERT(edx & (1 << 4), "TSC is not supported", "TSC is supported");
    SPRATCHER_ASSERT(edx & (1 << 5), "MSR is not supported", "MSR is supported");
    SPRATCHER_ASSERT(edx & (1 << 8), "CMOV is not supported", "CMOV is supported");
    SPRATCHER_ASSERT(edx & (1 << 11), "SYSCALL is not supported", "SYSCALL is supported");
    SPRATCHER_ASSERT(edx & (1 << 19), "SSE is not supported", "SSE is supported");
    SPRATCHER_ASSERT(edx & (1 << 26), "SSE2 is not supported", "SSE2 is supported");

    SPRATCHER_ASSERT(ecx & (1 << 0), "SSE3 is not supported", "SSE3 is supported");
    SPRATCHER_ASSERT(ecx & (1 << 9), "SSSE3 is not supported", "SSSE3 is supported");
    SPRATCHER_ASSERT(ecx & (1 << 12), "FMA is not supported", "FMA is supported");
    SPRATCHER_ASSERT(ecx & (1 << 19), "SSE4.1 is not supported", "SSE4.1 is supported");
    SPRATCHER_ASSERT(ecx & (1 << 20), "SSE4.2 is not supported", "SSE4.2 is supported");
    SPRATCHER_ASSERT(ecx & (1 << 23), "POPCNT is not supported", "POPCNT is supported");
    SPRATCHER_ASSERT(ecx & (1 << 25), "AES is not supported", "AES is supported");
    SPRATCHER_ASSERT(ecx & (1 << 28), "AVX is not supported", "AVX is supported");
    SPRATCHER_ASSERT(ecx & (1 << 30), "RDRAND is not supported", "RDRAND is supported");
    
    // CPUID(0x80000001): Extended Features
    if (eax >= 0x80000001) {
        __get_cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
        SPRATCHER_ASSERT(edx & (1 << 29), "NX is not supported", "NX is supported");
        SPRATCHER_ASSERT(ecx & (1 << 0), "F16C is not supported", "F16C is supported");
        SPRATCHER_ASSERT(edx & (1 << 23), "MMX is not supported", "MMX is supported");
        SPRATCHER_ASSERT(edx & (1 << 31), "3DNow! is not supported", "3DNow! is supported");

    }

    SPRATCHER_ASSERT(ebx & (1 << 28), "Hyper-Threading is not supported", "Hyper-Threading is supported");
    SPRATCHER_ASSERT(ecx & (1 << 5), "Intel VT-x is not supported", "Intel VT-x is supported");
    SPRATCHER_ASSERT(ecx & (1 << 2), "AMD SVM is not supported", "AMD SVM is supported");
    SPRATCHER_ASSERT(edx & (1 << 20), "Execute Disable (XD) is not supported", "Execute Disable (XD) is supported");
    SPRATCHER_ASSERT(ebx & (1 << 38), "Turbo Boost is not supported", "Turbo Boost is supported");
    SPRATCHER_ASSERT(edx & (1 << 0), "FPU is not supported", "FPU is supported");

    SpratcherCurrentStep = "Test FPOps";
    FLOAT test_floats = 1.0f;
    FLOAT test_floats2 = 2.0f;
    FLOAT test_floats3 = test_floats + test_floats2;
    SPRATCHER_ASSERT(test_floats3 == 3.0f, "Floating point operations are not supported", "Floating point operations are supported");

    KeDebugPrint("[ Done ] CPUID tests completed\n");
    KeDebugPrint("[ Done ] Stage 0 Complete.\n");
    KeDebugPrint("[ KILL ] Spratcher is now exiting...\n");

    return STATUS_SUCCESS; // for now, everything is just successful, we will add more checks later.
}
