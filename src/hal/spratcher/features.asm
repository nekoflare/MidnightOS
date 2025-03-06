bits 64

section .text

global KiAsmEnableAVX

KiAsmEnableAVX:
    push rax
    push rcx
    push rdx

    xor rcx, rcx
    xgetbv      ; Load XCR0 register
    or eax, 7   ; Set AVX, SSE, X87 bits
    xsetbv      ; Save back to XCR0

    pop rdx
    pop rcx
    pop rax
    ret