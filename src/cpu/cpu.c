//
// Created by Neko on 26.02.2025.
//

#include "cpu.h"

KERNEL_API void KiExplicitHalt()
{
    asm volatile ("cli; hlt");
}

KERNEL_API void KiExplicitDisableInterrupts() {
    asm volatile ("cli");
}

KERNEL_API void KiExplicitEnableInterrupts() {
    asm volatile ("sti");
}