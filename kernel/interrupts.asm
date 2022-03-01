bits 64

extern GeneralProtectionFault
extern ISRfunc

GeneralProtectionFault:
    jmp $

ISRfunc:
    iretq