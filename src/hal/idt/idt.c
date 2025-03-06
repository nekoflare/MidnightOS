#include "idt.h"
#include "raw_idt_table.h"
#include <hal/io.h>
#include <kdbg/debug_print.h>

static ULONGLONG KiReadControlRegister2()
{
    ULONGLONG cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    return cr2;
}

static void KiPrintPageFaultInfo(const INTERRUPT_STACK_FRAME *regs)
{
    // Print the faulting address from CR2
    ULONGLONG faulting_address = KiReadControlRegister2();
    KeDebugPrint("Linear address where the issue happened: %016lX\n", faulting_address);

    // Decode the error code
    UINT error_code = regs->ErrorCode;

    KeDebugPrint("The error has been caused by: ");

    if (error_code & (1 << 0))
    {
        KeDebugPrint("page-protection violation. ");
    }
    else
    {
        KeDebugPrint("non-present page. ");
    }

    if (error_code & (1 << 1))
    {
        KeDebugPrint("Write access. ");
    }
    else
    {
        KeDebugPrint("Read access. ");
    }

    if (error_code & (1 << 2))
    {
        KeDebugPrint("User mode. ");
    }
    else
    {
        KeDebugPrint("Kernel mode. ");
    }

    if (error_code & (1 << 3))
    {
        KeDebugPrint("Reserved bit violation. ");
    }

    if (error_code & (1 << 4))
    {
        KeDebugPrint("Instruction fetch. ");
    }

    if (error_code & (1 << 5))
    {
        KeDebugPrint("Protection key violation. ");
    }

    if (error_code & (1 << 6))
    {
        KeDebugPrint("Shadow stack access violation. ");
    }

    if (error_code & (1 << 15))
    {
        KeDebugPrint("SGX violation. ");
    }

    KeDebugPrint("\n");
}

static void KiPrintProcessorFlags(const ULONGLONG rflags)
{
    if (rflags & 0x00000001)
        KeDebugPrint("CF ");
    if (rflags & 0x00000004)
        KeDebugPrint("PF ");
    if (rflags & 0x00000010)
        KeDebugPrint("AF ");
    if (rflags & 0x00000040)
        KeDebugPrint("ZF ");
    if (rflags & 0x00000080)
        KeDebugPrint("SF ");
    if (rflags & 0x00000100)
        KeDebugPrint("TF ");
    if (rflags & 0x00000200)
        KeDebugPrint("IF ");
    if (rflags & 0x00000400)
        KeDebugPrint("DF ");
    if (rflags & 0x00000800)
        KeDebugPrint("OF ");
    if (rflags & 0x00010000)
        KeDebugPrint("RF ");
    if (rflags & 0x00020000)
        KeDebugPrint("VM ");
    if (rflags & 0x00040000)
        KeDebugPrint("AC ");
    if (rflags & 0x00080000)
        KeDebugPrint("VIF ");
    if (rflags & 0x00100000)
        KeDebugPrint("VIP ");
    if (rflags & 0x00200000)
        KeDebugPrint("ID ");
    if (rflags & 0x80000000)
        KeDebugPrint("AI ");
    KeDebugPrint("\n");
}

void KiPrintRegisters(const INTERRUPT_STACK_FRAME *regs)
{
    KeDebugPrint("RAX: %016lX RBX: %016lX RCX: %016lX RDX: %016lX\n", regs->RAX, regs->RBX, regs->RCX, regs->RDX);
    KeDebugPrint("RSI: %016lX RDI: %016lX RBP: %016lX RSP: %016lX\n", regs->RSI, regs->RDI, regs->RBP, regs->RSP);
    KeDebugPrint("R8:  %016lX R9:  %016lX R10: %016lX R11: %016lX\n", regs->R8, regs->R9, regs->R10, regs->R11);
    KeDebugPrint("R12: %016lX R13: %016lX R14: %016lX R15: %016lX\n", regs->R12, regs->R13, regs->R14, regs->R15);
    KeDebugPrint("DR0: %016lX DR1: %016lX DR2: %016lX DR3: %016lX\n", regs->DR0, regs->DR1, regs->DR2, regs->DR3);
    KeDebugPrint("DR4: %016lX DR5: %016lX DR6: %016lX DR7: %016lX\n", regs->DR4, regs->DR5, regs->DR6, regs->DR7);
    KeDebugPrint("CR0: %016lX CR2: %016lX CR3: %016lX CR4: %016lX CR8: %016lX\n", regs->CR0, regs->CR2, regs->CR3,
                 regs->CR4, regs->CR8);
    KeDebugPrint("CS:  %02lX  DS:  %02lX  SS:  %02lX  ES:  %02lX  FS:  %02lX GS: %02lX\n", regs->CS, regs->DS, regs->SS,
                 regs->ES, regs->FS, regs->GS);
    KeDebugPrint("RIP: %016lX\n", regs->RIP);
    KeDebugPrint("Orig RSP: %016lX CR3: %016lX\n", regs->OriginalRSP, regs->CR3);
    KeDebugPrint("Error code: %016lX Interrupt index: %016lX\n", regs->ErrorCode, regs->InterruptNumber);
    KeDebugPrint("RFLAGS: ");
    KiPrintProcessorFlags(regs->RFLAGS);
}

struct KGATE_DESCRIPTOR_64 KiCreateIDTEntry(void (*offset)(), uint16_t segment_selector, uint8_t gate_type,
                                            uint8_t dpl_layer, uint8_t is_present, uint8_t ist)
{
    struct KGATE_DESCRIPTOR_64 IDTEntry = {.OffsetLow = (uint16_t)((uint64_t)offset & 0xFFFF),
                                           .SegmentSelector = segment_selector,
                                           .IST = ist,
                                           .ReservedLow = 0,
                                           .GateType = gate_type,
                                           .Zero = 0,
                                           .DPL = dpl_layer,
                                           .Present = is_present,
                                           .OffsetMiddle = (uint16_t)(((uint64_t)offset & 0xFFFF0000) >> 16),
                                           .OffsetHigh = (uint32_t)(((uint64_t)offset & 0xFFFFFFFF00000000) >> 32),
                                           .ReservedHigh = 0};

    return IDTEntry;
}

extern void KiLoadIDTTable(struct KIDTR *idtr);

void KiInitializeIDT()
{
    PREVENT_DOUBLE_INIT

    struct KIDTR IdtRegister = {0};
    IdtRegister.Limit = sizeof(Idt) - 1;
    IdtRegister.Address = (ULONGLONG)&Idt;
    KiLoadIDTTableEntries();
    KiLoadIDTTable(&IdtRegister);

    asm volatile("sti");
}
