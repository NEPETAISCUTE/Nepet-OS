bits 64

section .text

extern term_write_ptr
extern atoi
extern GeneralProtectionFault
extern ISRfunc

GeneralProtectionFault:    
    pop rax

    mov rdi, GPFString
    call debugconPrint

    cmp rax, 0
    jz .end

    mov rdi, SegmentGPF
    call debugconPrint 

.end:
    jmp $

ISRfunc:
    iretq


debugconPrint:
    ;rdi = string
    push rax
.loop:
    mov al, [rdi]
    cmp al, 0
    jz .end
    out 0xE9, al
    inc rdi
    jmp .loop
.end:
    pop rax
    ret

section .data

GPFString: db "General Protection Fault occured", 0xA, 0
SegmentGPF: db "it is a segment error, segment selector index: ", 0