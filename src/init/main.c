//
// Created by Neko on 26.02.2025.
//

#include <stdbool.h>
#include <cpu/cpu.h>
#include <kernel.h>
#include <kdbg/debug_print.h>
#include <ke/error.h>
#include <ke/irql.h>
#include <ke/stacktrace.h>
#include <hal/spratcher/spinit.h>
#include <mm/physical.h>
#include <hal/initialize_arch.h>
#include <hal/io.h>
#include <ke/bugcheck.h>
#include <rtl/dlmalloc.h>
#include <string.h>

KERNEL_API void KernelMain(void) {
    // Initialize HAL component
    if (KeGetCurrentIrql() < HIGH_LEVEL)
        KeRaiseIrql(HIGH_LEVEL, NULL); // Ignore old IRQL
    KiInitializeDebugConn();
    KiSpratcherInit();
    void* last_malloc = NULL;
    for (int i = 0; i < 100; i++) {
        last_malloc = malloc(0x1000000);
        if (last_malloc == NULL) {
            KeDebugPrint("Failed to allocate memory\n");
            KeBugCheck(BUGCHECK_UNRECOVERABLE_NO_MEMORY);
        }
        KeDebugPrint("Allocated memory at %p\n", last_malloc);
        
    }
    
    KeDebugPrint("KernelMain() called\n");
    while (true) {
        KiExplicitHalt();
    }

    KeBugCheck(BUGCHECK_UNEXPECTED_STATE); // Should never reach here
}
