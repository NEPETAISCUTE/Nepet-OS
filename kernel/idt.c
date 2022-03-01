#include "idt.h"

struct InterruptDescriptor64 IDTdescriptor[33];
//sets the IDT table and then loads it in the IDTR
void set_idt()
{

    for(int i = 0; i < 33; i++)
    {
        IDTdescriptor[i].zero = 0;
        IDTdescriptor[i].selector = 0;
        IDTdescriptor[i].ist = 0;
        IDTdescriptor[i].type_attributes = 0;
        IDTdescriptor[i].offset_1 =  0;
        IDTdescriptor[i].offset_2 =  0;
        IDTdescriptor[i].offset_3 =  0;
    }

    IDTdescriptor[GENERAL_PROTECTION_FAULT].zero = 0;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].selector = 0x32<<3|SELECTOR_GDT_TABLE|0;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].ist = 0;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].type_attributes = 1<<7|GATE_TRAP;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].offset_1 =  (uint64_t)GeneralProtectionFault&0x000000000000FFFF;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].offset_2 =  ((uint64_t)GeneralProtectionFault&0x00000000FFFF0000)>>16;
    IDTdescriptor[GENERAL_PROTECTION_FAULT].offset_3 =  ((uint64_t)GeneralProtectionFault&0xFFFFFFFF00000000)>>32;

    IDTdescriptor[ISR].zero = 0;
    IDTdescriptor[ISR].selector = 0x28;
    IDTdescriptor[ISR].ist = 0;
    IDTdescriptor[ISR].type_attributes = 1<<7|GATE_ISR;
    IDTdescriptor[ISR].offset_1 =  (uint64_t)ISRfunc&0x000000000000FFFF;
    IDTdescriptor[ISR].offset_2 =  ((uint64_t)ISRfunc&0x00000000FFFF0000)>>16;
    IDTdescriptor[ISR].offset_3 =  ((uint64_t)ISRfunc&0xFFFFFFFF00000000)>>32;

    struct IDTRDescriptor descriptor;
    descriptor.size = 33*128-1;
    descriptor.offset = IDTdescriptor;
    struct IDTRDescriptor* descriptor_ptr = &descriptor;

    asm("lidt descriptor_ptr"
        "sti"
        : "=r" (descriptor_ptr));
}
