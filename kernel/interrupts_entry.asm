bits 64

section .rodata

GPFString: db "General Protection Fault occured", 0xA, 0
SegmentGPF: db "it is a segment error, segment selector index: ", 0

section .data

SegmentIndexString: resb 32

section .text

extern divByZErr ;INT 0x0
extern dbg ;INT 0x1
extern NMI ;INT 0x2
extern bkpt ;INT 0x3
extern overflow ;INT 0x4
extern boundRangeExceeded ;INT 0x5
extern invalidOPCode ;INT 0x6
extern deviceNotAvailable ;INT 0x7
extern doubleFault ;INT 0x8
extern invalidTSS ;INT 0xa
extern segmentNotPresent ;INT 0xb
extern stackSegmentFault ;INT 0xc
extern gpf ;INT 0xd
extern pageFault ;INT 0xe
extern x87FloatingPoint ;INT 0x10
extern alignmentCheck ;INT 0x11
extern machineCheck ;INT 0x12
extern SIMDFloatingPoint ;INT 0x13
extern virtualizationException ;INT 0x14
extern controlProtection ;INT 0x15
extern hypervisorInjection ;INT 0x1c
extern VMMCommunication ;INT 0x1d
extern securityException ;INT 0x1e
extern ISRfunc ;INT 0x20

extern divByZErr_asm ;INT 0x0
extern dbg_asm ;INT 0x1
extern NMI_asm ;INT 0x2
extern bkpt_asm ;INT 0x3
extern overflow_asm ;INT 0x4
extern boundRangeExceeded_asm ;INT 0x5
extern invalidOPCode_asm ;INT 0x6
extern deviceNotAvailable_asm ;INT 0x7
extern doubleFault_asm ;INT 0x8
extern invalidTSS_asm ;INT 0xa
extern segmentNotPresent_asm ;INT 0xb
extern stackSegmentFault_asm ;INT 0xc
extern GeneralProtectionFault_asm ;INT 0xd
extern pageFault_asm ;INT 0xe
extern x87FloatingPoint_asm ;INT 0x10
extern alignmentCheck_asm ;INT 0x11
extern machineCheck_asm ;INT 0x12
extern SIMDFloatingPoint_asm ;INT 0x13
extern virtualizationException_asm ;INT 0x14
extern controlProtection_asm ;INT 0x15
extern hypervisorInjection_asm ;INT 0x1c
extern VMMCommunication_asm ;INT 0x1d
extern securityException_asm ;INT 0x1e
extern ISRfunc_asm ;INT 0x20

divByZErr_asm:
    mov rdi, [rsp]
    call divByZErr
    iretq

dbg_asm:
    call dbg
    iretq

NMI_asm:
    call NMI
    iretq

bkpt_asm:
    call bkpt
    iretq

overflow_asm:
    call overflow
    iretq

boundRangeExceeded_asm:
    mov rdi, [rsp]
    call boundRangeExceeded_asm
    iretq

invalidOPCode_asm:
    mov rdi, [rsp]
    call invalidOPCode
    iretq

deviceNotAvailable_asm:
    mov rdi, [rsp]
    call deviceNotAvailable
    iretq

doubleFault_asm:
    call doubleFault
    hlt

invalidTSS_asm:
    pop rsi
    mov rdi, [rsp]
    call invalidTSS
    iretq

segmentNotPresent_asm:
    pop rsi
    mov rdi, [rsp]
    call segmentNotPresent
    iretq

stackSegmentFault_asm:
    pop rsi
    mov rdi, [rsp]
    call stackSegmentFault
    iretq

GeneralProtectionFault_asm:    
    pop rsi
    mov rdi, [rsp]
    call gpf
    iretq

pageFault_asm:
    mov rdx, cr2
    pop rsi
    mov rdi, [rsp]
    call pageFault
    iretq

x87FloatingPoint_asm:
    mov rdi, [rsp]
    call x87FloatingPoint
    iretq

alignmentCheck_asm:
    mov rdi, [rsp]
    call alignmentCheck
    iretq

machineCheck_asm:
    mov rdi, [rsp]
    call machineCheck
    iretq

SIMDFloatingPoint_asm:
    mov rdi, [rsp]
    call SIMDFloatingPoint
    iretq

virtualizationException_asm:
    mov rdi, [rsp]
    call virtualizationException
    iretq

controlProtection_asm:
    mov rdi, [rsp]
    call controlProtection
    iretq

hypervisorInjection_asm:
    mov rdi, [rsp]
    call hypervisorInjection
    iretq

VMMCommunication_asm:
    mov rdi, [rsp]
    call VMMCommunication
    iretq

securityException_asm:
    mov rdi, [rsp]
    call securityException
    iretq

ISRfunc_asm:
    call ISRfunc
    iretq