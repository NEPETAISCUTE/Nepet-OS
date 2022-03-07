bits 64

section .rodata

GPFString: db "General Protection Fault occured", 0xA, 0
SegmentGPF: db "it is a segment error, segment selector index: ", 0

section .data

SegmentIndexString: resb 32

section .text

extern term_write

extern gpf
extern ISRfunc

extern GeneralProtectionFault_asm
extern ISRfunc_asm

GeneralProtectionFault_asm:    
    pop rdi
    call gpf
    iretq

ISRfunc_asm:
    call ISRfunc
    iretq