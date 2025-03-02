#include "idt.h"
#include <kdbg/debug_print.h>
#include <hal/io.h>
#include "raw_idt_table.h"


static inline ULONGLONG read_cr2()
{
    ULONGLONG cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    return cr2;
}

static void print_page_fault_info(const INTERRUPT_STACK_FRAME *regs)
{
    // Print the faulting address from CR2
    ULONGLONG faulting_address = read_cr2();
    KeDebugPrint("Linear address where the issue happened: %016lX\n", faulting_address);

    // Decode the error code
    UINT error_code = regs->error_code;

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

static void print_processor_flags(const ULONGLONG rflags)
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
    KeDebugPrint("RAX: %016lX RBX: %016lX RCX: %016lX RDX: %016lX\n", regs->rax, regs->rbx, regs->rcx, regs->rdx);
    KeDebugPrint("RSI: %016lX RDI: %016lX RBP: %016lX RSP: %016lX\n", regs->rsi, regs->rdi, regs->rbp, regs->rsp);
    KeDebugPrint("R8:  %016lX R9:  %016lX R10: %016lX R11: %016lX\n", regs->r8, regs->r9, regs->r10, regs->r11);
    KeDebugPrint("R12: %016lX R13: %016lX R14: %016lX R15: %016lX\n", regs->r12, regs->r13, regs->r14, regs->r15);
    KeDebugPrint("DR0: %016lX DR1: %016lX DR2: %016lX DR3: %016lX\n", regs->dr0, regs->dr1, regs->dr2, regs->dr3);
    KeDebugPrint("DR4: %016lX DR5: %016lX DR6: %016lX DR7: %016lX\n", regs->dr4, regs->dr5, regs->dr6, regs->dr7);
    KeDebugPrint("CR0: %016lX CR2: %016lX CR3: %016lX CR4: %016lX CR8: %016lX\n", regs->cr0, regs->cr2, regs->cr3,
                regs->cr4, regs->cr8);
    KeDebugPrint("CS:  %02lX  DS:  %02lX  SS:  %02lX  ES:  %02lX  FS:  %02lX GS: %02lX\n", regs->cs, regs->ds, regs->ss,
                regs->es, regs->fs, regs->gs);
    KeDebugPrint("RIP: %016lX\n", regs->rip);
    KeDebugPrint("Orig RSP: %016lX CR3: %016lX\n", regs->orig_rsp, regs->cr3);
    KeDebugPrint("Error code: %016lX Interrupt index: %016lX\n", regs->error_code, regs->interrupt_number);
    KeDebugPrint("RFLAGS: ");
    print_processor_flags(regs->rflags);
}


struct GATE_DESCRIPTOR_64 KiCreateIDTEntry(void (*offset)(), uint16_t segment_selector, uint8_t gate_type, uint8_t dpl_layer, uint8_t is_present, uint8_t ist)
{
    struct GATE_DESCRIPTOR_64 a = {
        .offset_one = (uint16_t)((uint64_t)offset & 0xFFFF),
        .segment_selector = segment_selector,
        .ist = ist,
        .reserved_one = 0,
        .gate_type = gate_type,
        .zero = 0,
        .dpl = dpl_layer,
        .present = is_present,
        .offset_two = (uint16_t)(((uint64_t)offset & 0xFFFF0000) >> 16),
        .offset_three = (uint32_t)(((uint64_t)offset & 0xFFFFFFFF00000000) >> 32),
        .reserved_two = 0
    };

    return a;
}

extern void KiLoadIDTTable(struct IDTR *idtr);

void KiInitializeIDT()
{
    KeDebugPrint("Initializing IDT\n");
    struct IDTR idt_register = {0};
    idt_register.limit = sizeof(idt) - 1;
    idt_register.idt_address = (ULONGLONG)&idt;
    KiLoadIDTTableEntries();
    KiLoadIDTTable(&idt_register);

    asm volatile("sti");
    KeDebugPrint("IDT initialized\n");
}
