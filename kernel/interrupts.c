#include <interrupts.h>

void (*term_write_int)(const char* string, size_t length) = NULL;

void gpf(int errorCode)
{
    term_write_int("\x1b[1;31mGeneral Protection Fault occured\n", 33);
}

void ISRfunc()
{
    term_write_int("ISR has acces to term_write\n",28);
    return;
}