#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

void itoa(char* s, int n);
void itohex(char* s, uint64_t n);
int atoi(char* s);
void strcpy(char* dest, const char* src, size_t maxLen);
size_t strlen(char* s);
void concat(char* s, const char* sadd);

#endif