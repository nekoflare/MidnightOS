//
// Created by Neko on 28.02.2025.
//

#include "initialize_arch.h"
#include <kdbg/debug_print.h>
#include "gdt/gdt.h"
#include "idt/idt.h"

KERNEL_API void KiInitializeHAL()
{
    KeDebugPrint("Initializing HAL...\n");
    KiInitializeGDT();
    KiInitializeIDT();
    KeDebugPrint("HAL initialized\n");
}