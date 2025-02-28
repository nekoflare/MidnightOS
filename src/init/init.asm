bits 64

section .text

enable_sse:
    mov rax, cr0
    and ax, 0xfffb
    or ax, 0x2
    mov cr0, rax

    mov rax, cr4
    or ax, 3 << 9
    mov cr4, rax

    ret

global _start
extern KernelMain
_start:
    xchg bx, bx

    ; Align stack
    and rsp, 0xfffffffffffffff0

    ; Enable SSE (explicit)
    call enable_sse

    ; Jump to kernel
    call KernelMain