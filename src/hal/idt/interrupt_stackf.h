#ifndef INTERRUPT_STACK_FRAME_H
#define INTERRUPT_STACK_FRAME_H

#include <kernel.h>
typedef struct {
    ULONGLONG dr0;
    ULONGLONG dr1;
    ULONGLONG dr2;
    ULONGLONG dr3;
    ULONGLONG dr4;
    ULONGLONG dr5;
    ULONGLONG dr6;
    ULONGLONG dr7;
    ULONGLONG cr0;
    ULONGLONG cr2;
    ULONGLONG cr3;
    ULONGLONG cr4;
    ULONGLONG cr8;
    ULONGLONG gs;
    ULONGLONG fs;
    ULONGLONG es;
    ULONGLONG ds;
    ULONGLONG r15;
    ULONGLONG r14;
    ULONGLONG r13;
    ULONGLONG r12;
    ULONGLONG r11;
    ULONGLONG r10;
    ULONGLONG r9;
    ULONGLONG r8;
    ULONGLONG rdi;
    ULONGLONG rsi;
    ULONGLONG rbp;
    ULONGLONG rsp;
    ULONGLONG rdx;
    ULONGLONG rcx;
    ULONGLONG rbx;
    ULONGLONG rax;
    ULONGLONG interrupt_number;
    ULONGLONG error_code;
    ULONGLONG rip;
    ULONGLONG cs;
    ULONGLONG rflags;
    ULONGLONG orig_rsp;
    ULONGLONG ss;
} __attribute__((packed)) INTERRUPT_STACK_FRAME;

#endif // INTERRUPT_STACK_FRAME_H