#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern void (*term_write)(const char* string, size_t length);

#endif
