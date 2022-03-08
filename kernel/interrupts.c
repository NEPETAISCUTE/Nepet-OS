#include <interrupts.h>

void printRIP(void* IP)
{
    char RIP[17];
    itohex(RIP, (uint64_t)IP);
    term_write("RIP=0x",6);
    term_write(RIP,strlen(RIP));
    term_write("\n", 1);
}

inline void setColorError()
{
    term_write("\x1b[1;31m", 7);
}

//INT 0x0
void divByZErr(void* InstructionPointer)
{
    setColorError();
    term_write("Divide By Zero Fault occured\n", 29);

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0x1
void dbg()
{
    setColorError();
    term_write("Debug trap triggered!\n", 22);
    term_write("debug isn't implemented yet...\n", 31);
}

//INT 0x2
void NMI()
{
    setColorError();
    term_write("NMI occured!\n", 13);
    term_write("NMI is not supported yet...\n", 28);

    asm("hlt");
}

//INT 0x3
void bkpt()
{
    setColorError();
    term_write("bkpt occured, proceeding\n", 25);
}

//INT 0x4
void overflow()
{
    setColorError();
    term_write("overflow occured, proceeding\n", 29);
}

//INT 0x5
void boundRangeExceeded(void* InstructionPointer)
{
    setColorError();
    term_write("Bound Range Exceeded Fault occured\n", 35);

    printRIP(InstructionPointer);

    asm("hlt");;
}

//INT 0x6
void invalidOPCode(void* InstructionPointer)
{
    setColorError();
    term_write("Invalid OPCode Fault occured\n", 29);

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0x7
void deviceNotAvailable(void* InstructionPointer)
{
    setColorError();
    term_write("Device Not Available Fault occured\n", 35);

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0x8
void doubleFault()
{
    setColorError();
    term_write("Double Fault occured\n", 21);
    term_write("no RIP available since double Fault isn't recoverable\n", 54);

    asm("hlt");
}

//INT 0xa
void invalidTSS(void* InstructionPointer, int selectorIndex)
{
    setColorError();
    term_write("Invalid TSS Fault occured\n", 26);

    char selectorIndexString[17];
    itohex(selectorIndexString, selectorIndex);
    term_write("Selector index: ", 16);
    term_write(selectorIndexString, strlen(selectorIndexString));
    term_write("\n", 1);

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0xb
void segmentNotPresent(void* InstructionPointer, int segmentSelectorIndex)
{
    setColorError();
    term_write("Segment Not Present Fault occured\n", 34);

    char segmentSelectorIndexString[17];
    itohex(segmentSelectorIndexString, segmentSelectorIndex);
    term_write("Segment selector index: ", 24);
    term_write(segmentSelectorIndexString, strlen(segmentSelectorIndexString));
    term_write("\n", 1);

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0xc
void stackSegmentFault(void* InstructionPointer, int segmentSelectorIndex)
{
    setColorError();
    term_write("Stack-Segment Fault occured\n", 28);

    char valString[17];
    if(segmentSelectorIndex!=0)
    {
        itohex(valString, segmentSelectorIndex);
        term_write("Stack segment selector index: ", 30);
        term_write(valString, strlen(valString));
    }

    printRIP(InstructionPointer);

    asm("hlt");
}

//INT 0xd
void gpf(void* InstructionPointer, int errorCode)
{
    setColorError();
    term_write("General Protection Fault occured\n", 33);
    uint8_t tType = 0;
    char segSelectorText[17];
    if(errorCode!=0)
    {
        term_write("the error is Segment related!\n",30);

        if(errorCode&0b1)
        {
            term_write("the exception is external to the processor\n",43);
        }
        
        tType = (errorCode>>1)&0b11;
        term_write("table: ", 7);
        switch(tType)
        {
            case 0:
                term_write("GDT\n",4);
                break;
            case 1:
                term_write("IDT\n",4);
                break;
            case 2:
                term_write("LDT\n",4);
                break;
            case 3:
                term_write("IDT\n",4);
                break;
        }

        itohex(segSelectorText, (uint16_t)(errorCode)>>3);
        term_write("selector index: 0x", 18);
        term_write(segSelectorText, strlen(segSelectorText));

        term_write("\nwhole error code: ", 19);
        itohex(segSelectorText, errorCode);
        term_write("0x", 2);
        term_write(segSelectorText, strlen(segSelectorText));
        term_write("\n", 1);
    }

    printRIP(InstructionPointer);

    asm("hlt");
}

void pageFault(void* InstructionPointer, int errorCode, void* virtualAddress)
{
    setColorError();
    term_write("Page Fault occured\n", 19);

    if(errorCode&0b1) //P
        term_write("page protection violation\n", 26);
    else
        term_write("page not present\n", 17);

    if((errorCode>>1)&0b1) //W
        term_write("caused by write access\n", 23);
    else
        term_write("caused by read access\n", 22);
    
    if((errorCode>>2)&0b1) //U
        term_write("CPL is equal to 3\n", 18);

    if((errorCode>>3)&0b1) //R
        term_write("at least one page has reserved bit set\n", 39);
    
    if((errorCode>>4)&0b1) //I
        term_write("the fault was caused by an instruction fetch\n", 45);
    
    if((errorCode>>5)&0b1) //PK
        term_write("the fault was caused by a protective key violation\n", 51);
    
    if((errorCode>>6)&0b1) //SS
        term_write("the fault was caused by a shadow stack access\n", 46);

    if((errorCode>>15)&0b1) //SGX
        term_write("the fault was caused by SGX\n", 28);
    
    char virtAddress[17];
    itohex(virtAddress, (uint64_t)virtualAddress);
    term_write("virtual address: 0x", 19);
    term_write(virtAddress, strlen(virtAddress));
    term_write("\n", 1);
    
    printRIP(InstructionPointer);

    asm("hlt");
}

void x87FloatingPoint(void* InstructionPointer)
{
    setColorError();
    term_write("x87 Floating-Point Exception occured\n", 37);

    printRIP(InstructionPointer);

    asm("hlt");
}

void alignmentCheck(void* InstructionPointer)
{
    setColorError();
    term_write("Alignment Check got triggered\n", 30);

    printRIP(InstructionPointer);

    asm("hlt");
}

void machineCheck(void* InstructionPointer)
{
    setColorError();
    term_write("Machine Check got triggered\n", 28);

    printRIP(InstructionPointer);

    asm("hlt");
}

void SIMDFloatingPoint(void* InstructionPointer)
{
    setColorError();
    term_write("SIMD Floating-Point Fault occured\n", 34);

    printRIP(InstructionPointer);

    asm("hlt");
}

void virtualizationException(void* InstructionPointer)
{
    setColorError();
    term_write("Virtualization Exception occured\n", 33);

    printRIP(InstructionPointer);

    asm("hlt");
}

void controlProtection(void* InstructionPointer)
{
    setColorError();
    term_write("Control Protection Fault occured\n", 33);

    printRIP(InstructionPointer);

    asm("hlt");
}

void hypervisorInjection(void* InstructionPointer)
{
    setColorError();
    term_write("Hypervisor Injection Fault occured\n", 35);

    printRIP(InstructionPointer);

    asm("hlt");
}

void VMMCommunication(void* InstructionPointer)
{
    setColorError();
    term_write("VMM Communication Fault occured\n", 32);

    printRIP(InstructionPointer);

    asm("hlt");
}

void securityException(void* InstructionPointer)
{
    setColorError();
    term_write("Security Exception occured\n", 27);

    printRIP(InstructionPointer);

    asm("hlt");
}

void ISRfunc()
{
    term_write("ISR 0 has access to term_write\n",31);
    return;
}