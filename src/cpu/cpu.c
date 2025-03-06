//
// Created by Neko on 26.02.2025.
//

#include "cpu.h"
#include <cpuid.h>
#include <kernel.h>

KERNEL_API void KiExplicitHalt()
{
    asm volatile("cli; hlt");
}

KERNEL_API void KiExplicitDisableInterrupts()
{
    asm volatile("cli");
}

KERNEL_API void KiExplicitEnableInterrupts()
{
    asm volatile("sti");
}

KERNEL_API void KeGetCpuName(char *name)
{
    __get_cpuid(0, NULL, NULL, NULL, NULL);
    __get_cpuid(0x80000002, (PUINT)name, (PUINT)(name + 4), (PUINT)(name + 8), (PUINT)(name + 12));
    __get_cpuid(0x80000003, (PUINT)(name + 16), (PUINT)(name + 20), (PUINT)(name + 24), (PUINT)(name + 28));
    __get_cpuid(0x80000004, (PUINT)(name + 32), (PUINT)(name + 36), (PUINT)(name + 40), (PUINT)(name + 44));
    name[48] = 0;
}

KERNEL_API void KeGetCpuVendorRaw(char *vendor)
{
    __get_cpuid(0, NULL, (PUINT)vendor, (PUINT)(vendor + 8), (PUINT)(vendor + 4));
    vendor[12] = 0;
}