//
// Created by Neko on 28.02.2025.
//

#include "initialize_arch.h"

#include "gdt/gdt.h"

KERNEL_API void KiInitializeHAL()
{
    KiInitializeGDT();
}