#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>

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

struct InterruptDescriptor64{
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
};
struct IDTRDescriptor {
    uint16_t size;
    struct InterruptDescriptor64* offset;
};

extern void ISRfunc();
extern void GeneralProtectionFault();
void set_idt();

#endif