#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>
#include <string.h>
#include <video.h>

#define IST_STACK_UNUSED 0

#define GATE_ISR 0xE
#define GATE_TRAP 0xF

#define SELECTOR_GDT_TABLE 0x0
#define SELECTOR_IDT_TABLE 0x4

enum interrupts {
    DIV_BY_ZERO,
    DEBUG,
    NMI,
    BKPT,
    OVERFLOW,
    BOUND_RANGE,
    INVALID_OP,
    DEVICE_NOT_AVAILABLE,
    DOUBLE_FAULT,
    INVALID_TSS = 0xa,
    SEGMENT_NOT_PRESENT,
    STACK_SEGMENT_FAULT,
    GENERAL_PROTECTION_FAULT,
    PAGE_FAULT,
    X87_FLOATING_POINT_EXCEPTION = 0x10,
    ALIGNMENT_CHECK,
    MACHINE_CHECK,
    SIMD_FLOATING_POINT_EXCEPTION,
    VIRTUALIZATION_EXCEPTION,
    CONTROL_PROTECTION_EXCEPTION,
    HYPERVISOR_INJECTION_EXCEPTION = 0x1c,
    VMM_COMMUNICATION_EXCEPTION,
    SECURITY_EXCEPTION,
    ISR = 0x20,
};

struct  InterruptDescriptor64{
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
}__attribute__((__packed__)); ;

struct  IDTRDescriptor {
    uint16_t size;
    struct InterruptDescriptor64* offset;
}__attribute__((__packed__)); ;

extern void (*term_write)(const char *string, size_t length);

extern void divByZErr_asm(); //INT 0x0
extern void dbg_asm(); //INT 0x1
extern void NMI_asm(); //INT 0x2
extern void bkpt_asm(); //INT 0x3
extern void overflow_asm(); //INT 0x4
extern void boundRangeExceeded_asm(); //INT 0x5
extern void invalidOPCode_asm(); //INT 0x6
extern void deviceNotAvailable_asm(); //INT 0x7
extern void doubleFault_asm(); //INT 0x8
extern void invalidTSS_asm(); //INT 0xA
extern void segmentNotPresent_asm(); //INT 0xb
extern void stackSegmentFault_asm(); //INT 0xc
extern void GeneralProtectionFault_asm(); //INT 0xd
extern void pageFault_asm(); //INT 0xe
extern void x87FloatingPoint_asm(); //INT 0x10
extern void alignmentCheck_asm(); //INT 0x11
extern void machineCheck_asm(); //INT 0x12
extern void SIMDFloatingPoint_asm(); //INT 0x13
extern void virtualizationException_asm(); //INT 0x14
extern void controlProtection_asm(); //INT 0x15
extern void hypervisorInjection_asm(); //INT 0x1c
extern void VMMCommunication_asm(); //INT 0x1d
extern void securityException_asm(); //INT 0x1e
extern void kbIRQ_asm(); //INT 0x20

void nullifyGate(uint8_t gateOffset);
void setGate(uint8_t gateOffset, uint8_t attributes, void* codeInterrupt);
void set_idt();

#endif