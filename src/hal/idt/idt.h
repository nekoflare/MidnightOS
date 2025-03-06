//
// Created by Neko on 20.01.2025.
//

#ifndef IDT_H
#define IDT_H
#include "interrupt_stackf.h"
#include <kernel.h>

struct KIDTR
{
    USHORT Limit;
    ULONGLONG Address;
} __attribute__((packed));

struct KGATE_DESCRIPTOR_64
{
    USHORT OffsetLow;
    USHORT SegmentSelector;
    UCHAR IST : 3;
    UCHAR ReservedLow : 5;
    UCHAR GateType : 4;
    UCHAR Zero : 1;
    UCHAR DPL : 2;
    UCHAR Present : 1;
    USHORT OffsetMiddle;
    UINT OffsetHigh;
    UINT ReservedHigh;
} __attribute__((packed));

#define IDT_GATE_TYPE_INTERRUPT 0xE
#define IDT_GATE_TYPE_TRAP_GATE 0xF
#define IDT_DPL_RING_0 0
#define IDT_DPL_RING_1 1
#define IDT_DPL_RING_2 2
#define IDT_DPL_RING_3 3
#define IDT_PRESENT 1
#define IDT_NO_IST 0
#define IDT_DEFAULT_SEGMENT 0x8

struct KGATE_DESCRIPTOR_64 KiCreateIDTEntry(void (*offset)(), uint16_t segment_selector, uint8_t gate_type,
                                            uint8_t dpl_layer, uint8_t is_present, uint8_t ist);

extern volatile struct KGATE_DESCRIPTOR_64 Idt[256];

void KiInitializeIDT();
void KiPrintRegisters(const INTERRUPT_STACK_FRAME *regs);

#endif // IDT_H
