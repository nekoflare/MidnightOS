//
// Created by Neko on 26.02.2025.
//

#include <stdbool.h>
#include <cpu/cpu.h>
#include <kernel.h>
#include <kdbg/debug_print.h>
#include <ke/irql.h>

#include "hal/initialize_arch.h"
#include "hal/io.h"

KERNEL_API void KernelMain(void) {
    // Initialize HAL component
    if (KeGetCurrentIrql() < HIGH_LEVEL)
        KeRaiseIrql(HIGH_LEVEL, NULL); // Ignore old IRQL
    KiExplicitDisableInterrupts();
    KiInitializeDebugConn();
    KiInitializeHAL();

    KeDebugPrint("Hello, world!");

    while (true) {
        KiExplicitHalt();
    }
}
