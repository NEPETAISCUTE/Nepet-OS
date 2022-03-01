bits 64
extern ISRfunc
extern GeneralProtectionFault
ISRfunc:
    iretq

GeneralProtectionFault:
    jmp $