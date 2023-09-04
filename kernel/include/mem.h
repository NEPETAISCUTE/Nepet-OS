#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

enum bitmapStatus {
    FREE,
    USED
};

//inits the bitmap of the allocator
void initbitmap();
//not really useful, unless you wanna set a specific bit of an uint8_t or clear it
void setbit(uint8_t* byte, uint8_t bitIndex, enum bitmapStatus val);
//just to find a bit in a byte
uint16_t findbit(uint8_t byte, uint8_t bit);
//checks that the size required fits at the address given
int checksize(uint32_t bitIndex, uint16_t size);
//allocates an array of a certain size, if there's no memory left for it in the huge array intended, it'll return null
void* bitmalloc(uint16_t size);
//allocates an array based on a length and a blockSize, and then, initializes it all to 0.
void* bitcalloc(uint16_t length, uint8_t blockSize);

#endif