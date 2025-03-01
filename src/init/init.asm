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
    ; Align stack (to 8 bytes but after push itll be 16 bytes)
    and rsp, 0xfffffffffffffff8

    ; Enable SSE (explicit)
    call enable_sse

    xor rbp, rbp
    push rbp ; For the sake of the stack frame

    ; Jump to kernel
    call KernelMain