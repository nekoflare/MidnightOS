//
// Created by Neko on 26.02.2025.
//

#include "gdt.h"
#include <kdbg/debug_print.h>

struct GDT_SEGMENT_DESCRIPTOR gdt[] = {
    // NULL
    GDT_ENTRY(0, 0, 0, 0),

    // Kernel Code & data
    GDT_ENTRY(0, 0, GDT_PRESENT | GDT_DPL0 | GDT_EXECUTABLE_BIT | GDT_DESCRIPTOR_TYPE_BIT | GDT_READ_WRITE_BIT,
              GDT_LONG_MODE_FLAG | GDT_GRANULARITY_FLAG),
    GDT_ENTRY(0, 0, GDT_PRESENT | GDT_DPL0 | GDT_DESCRIPTOR_TYPE_BIT | GDT_READ_WRITE_BIT,
              GDT_SIZE_FLAG | GDT_GRANULARITY_FLAG),

    // User code & data
    GDT_ENTRY(0, 0, GDT_PRESENT | GDT_DPL3 | GDT_EXECUTABLE_BIT | GDT_DESCRIPTOR_TYPE_BIT | GDT_READ_WRITE_BIT,
              GDT_LONG_MODE_FLAG | GDT_GRANULARITY_FLAG),
    GDT_ENTRY(0, 0, GDT_PRESENT | GDT_DPL3 | GDT_DESCRIPTOR_TYPE_BIT | GDT_READ_WRITE_BIT,
              GDT_SIZE_FLAG | GDT_GRANULARITY_FLAG),

    // TSS space
    GDT_ENTRY(0, 0, 0, 0),
    GDT_ENTRY(0, 0, 0, 0),
};

KERNEL_API void KiInitializeGDT()
{
    PREVENT_DOUBLE_INIT
    KeDebugPrint("Initializing GDT...\n");
    struct GDTR gdtr = {.Size = sizeof(gdt) - 1, .GdtAddress = (ULONGLONG)&gdt};

    KiFlushGDT(&gdtr);
    KeDebugPrint("GDT initialized\n");
}