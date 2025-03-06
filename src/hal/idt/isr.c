#include <hal/idt/idt.h>
#include <hal/io.h>
#include <kdbg/debug_print.h>
#include <ke/bugcheck.h>
#include <ke/stacktrace.h>

#include "interrupt_stackf.h"
const char *ExceptionStrings[32] = {"(#DE) Division Error",
                                    "(#DB) Debug",
                                    "(#--) Non-maskable Interrupt",
                                    "(#BP) Breakpoint",
                                    "(#OF) Overflow",
                                    "(#BR) Bound Range Exceeded",
                                    "(#UD) Invalid Opcode",
                                    "(#NM) Device Not Available",
                                    "(#DF) Double Fault",
                                    "(#--) Coprocessor Segment Overrun",
                                    "(#TS) Invalid TSS",
                                    "(#NP) Segment Not Present",
                                    "(#SS) Stack Segment Fault",
                                    "(#GP) General Protection Fault",
                                    "(#PF) Page Fault",
                                    "(#--) Reserved",
                                    "(#MF) x87 Floating-Point Exception",
                                    "(#AC) Alignment Check",
                                    "(#MC) Machine Check",
                                    "(#XM) SIMD Floating-Point Exception",
                                    "(#VE) Virtualization Exception",
                                    "(#CP) Control Protection Exception",
                                    "",
                                    "",
                                    "",
                                    "",
                                    "",
                                    "",
                                    "(#HV) Hypervisor Injection Exception",
                                    "(#VC) VMM Communication Exception",
                                    "(#SX) Security Exception",
                                    "(#--) Reserved"};
/* ISR Handler */
void KiInterruptHandler(INTERRUPT_STACK_FRAME *frame)
{
    if (frame->InterruptNumber < 32)
    {
        KeDebugPrint("[-------------------- FATAL ERROR --------------------]\n");
        KeDebugPrint("Interrupt: %s\n", ExceptionStrings[frame->InterruptNumber]);
        KiPrintRegisters(frame);

        KeDebugPrint("[-------------------- STACK TRACE --------------------]\n");
        KeWalkStack(256);
        KeDebugPrint("[-----------------------------------------------------]\n");
        KeBugCheck(BUGCHECK_UNEXPECTED_STATE);
    }

    struct KIO_PORT_DESCRIPTOR port = {0};
    KiCreatePortResource(&port, IOP_ATTRIBUTE_WRITABLE, 0x20, 0x20);
    KiWritePortByte(&port, 0x20, 0x20);
    KiDestroyPortResource(&port);
    KiCreatePortResource(&port, IOP_ATTRIBUTE_WRITABLE, 0xA0, 0xA0);
    KiWritePortByte(&port, 0xA0, 0x20);
    KiDestroyPortResource(&port);
}
