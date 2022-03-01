#include "idt.h"

struct InterruptDescriptor64 IDTdescriptor[33];
//sets the IDT table and then loads it in the IDTR
void set_idt()
{

    for(int i = 0; i < 33; i++)
    {
        nullifyGate(i);
    }

    setGate(GENERAL_PROTECTION_FAULT, GATE_TRAP, GeneralProtectionFault);

    setGate(ISR, GATE_ISR, ISRfunc);

    struct IDTRDescriptor descriptor;
    descriptor.size = sizeof(IDTdescriptor)-1;
    descriptor.offset = IDTdescriptor;

    asm volatile("lidt %0\n"
        "sti\n"
        :
        : "m" (descriptor));
}

void nullifyGate(uint8_t gateOffset)
{
    IDTdescriptor[gateOffset].zero = 0;
    IDTdescriptor[gateOffset].selector = 0;
    IDTdescriptor[gateOffset].ist = 0;
    IDTdescriptor[gateOffset].type_attributes = 0;
    IDTdescriptor[gateOffset].offset_1 =  0;
    IDTdescriptor[gateOffset].offset_2 =  0;
    IDTdescriptor[gateOffset].offset_3 =  0;
}

void setGate(uint8_t gateOffset, uint8_t attributes, void* codeInterrupt)
{
    IDTdescriptor[gateOffset].zero = 0;
    IDTdescriptor[gateOffset].selector = 0x28;
    IDTdescriptor[gateOffset].ist = 0;
    IDTdescriptor[gateOffset].type_attributes = 1<<7|attributes;
    IDTdescriptor[gateOffset].offset_1 =  (uint64_t)codeInterrupt&0x000000000000FFFF;
    IDTdescriptor[gateOffset].offset_2 =  ((uint64_t)codeInterrupt&0x00000000FFFF0000)>>16;
    IDTdescriptor[gateOffset].offset_3 =  ((uint64_t)codeInterrupt&0xFFFFFFFF00000000)>>32;
}