//
// Created by Neko on 26.02.2025.
//

#include <stdbool.h>
#include <cpu/cpu.h>
#include <kernel.h>
#include <kdbg/debug_print.h>
#include <ke/irql.h>
#include <hal/spratcher/spinit.h>
#include <ke/bugcheck.h>
#include <hal/initialize_arch.h>
#include <mm/virtual.h>
#include <mm/vmem-allocator.h>
#include <rtl/dlmalloc.h>
#include <rtl/runtime.h>

KERNEL_API void KernelMain(void) {
    // Initialize HAL component
    if (KeGetCurrentIrql() < HIGH_LEVEL)
        KeRaiseIrql(HIGH_LEVEL, NULL); // Ignore old IRQL
    KiInitializeDebugPort();
    KiSpratcherInit();

    KeDebugPrint("KernelMain() called\n");
    while (true) {
        KiExplicitHalt();
    }

    KeBugCheck(BUGCHECK_UNEXPECTED_STATE); // Should never reach here
}
