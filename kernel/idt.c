#include <idt.h>

struct InterruptDescriptor64 IDTdescriptor[33];
//sets the IDT table and then loads it in the IDTR
void set_idt()
{
    for(int i = 0; i < 33; i++)
    {
        nullifyGate(i);
    }

    const uint8_t attributes[33] = {
        GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP,
        GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP,
        GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP,
        GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP,
        GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP, GATE_TRAP,
        GATE_TRAP, GATE_TRAP, GATE_ISR
    };

    void* interruptFuncs[] = {
        divByZErr_asm, dbg_asm, NMI_asm, bkpt_asm, overflow_asm, boundRangeExceeded_asm, invalidOPCode_asm,
        deviceNotAvailable_asm, doubleFault_asm, NULL, invalidTSS_asm, segmentNotPresent_asm, stackSegmentFault_asm,
        GeneralProtectionFault_asm, pageFault_asm, NULL, x87FloatingPoint_asm, alignmentCheck_asm, machineCheck_asm,
        SIMDFloatingPoint_asm, virtualizationException_asm, controlProtection_asm, NULL, NULL, NULL, NULL, NULL, NULL, hypervisorInjection_asm, VMMCommunication_asm,
        securityException_asm, NULL, kbIRQ_asm
    };

    char iString[17];
    for(int i = 0; i < (int)sizeof(interruptFuncs)/8; i++)
    {   
        itohex(iString, (uint64_t)i);
        term_write("setting interrupt 0x", 20);
        term_write(iString, strlen(iString));

        if(interruptFuncs[i]==NULL)
        {
            term_write(" to NULL",8);
            nullifyGate(i);
        }
        else
        {
            itohex(iString, (uint64_t)interruptFuncs[i]);
            term_write(" to 0x", 6);
            term_write(iString, strlen(iString));

            if(attributes[i]==GATE_TRAP)
                term_write(" (TRAP GATE)", 12);
            else
                term_write(" (ISR GATE)", 11);
            setGate(i, attributes[i], interruptFuncs[i]);
        }

        term_write("\n", 1);
    }

    struct IDTRDescriptor descriptor;
    descriptor.size = sizeof(IDTdescriptor)-1;
    descriptor.offset = IDTdescriptor;

    asm volatile(
        "lidt %0\n"
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