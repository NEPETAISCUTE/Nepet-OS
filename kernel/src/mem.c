#include "mem.h"

uint8_t bitmap[(1<<15)/8];
uint8_t arena[1<<15];

void setbit(uint8_t* byte, uint8_t bitIndex, enum bitmapStatus val)
{
    *byte = *byte|(val<<bitIndex);
}

int checksize(uint32_t bitIndex, uint16_t size)
{
    uint16_t byteIndex = bitIndex/8;
    uint16_t maxByteIndex = byteIndex + size/8;
    bitIndex = bitIndex%8;
    uint8_t maxBitIndex = bitIndex + size%8;
    for(byteIndex; byteIndex < maxByteIndex; byteIndex++)
    {
        for(bitIndex; bitIndex < 8; bitIndex++)
        {
            if((bitmap[byteIndex])&(0b1<<bitIndex))
            {
                return 0;
            }
            if(byteIndex==maxByteIndex && bitIndex==maxBitIndex)
                break;
        }
        bitIndex = 0;
    }
    return 1;
}

void initbitmap()
{
    for(int i = 0; i < sizeof(arena); i++)
        setbit(&bitmap[i/8], i%8, FREE);
}

void* bitmalloc(uint16_t size)
{
    uint16_t byteIndex;
    uint8_t bitIndex = 0;
    void* rpointer = NULL;
    uint16_t tempbyte;
    uint8_t tempbit;
    uint8_t done = 0;
    for(byteIndex = 0; byteIndex < sizeof(bitmap); byteIndex++)
    {
        for(bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            if(!(bitmap[byteIndex]&(USED<<bitIndex)) && checksize(byteIndex*8+bitIndex, size))
            {
                rpointer = &arena[byteIndex*8+bitIndex];
                tempbyte = byteIndex;
                tempbit = bitIndex;
                for(int i = 0; i < size; i++)
                {
                    setbit(&bitmap[tempbyte], tempbit, USED);
                    tempbit++;
                    if(tempbit>7)
                    {
                        tempbyte++;
                        tempbit=0;
                    }
                }
                done = 1;
                break;
            }
        }
        if(done)
            break;
    }
    return rpointer;
}

void* bitcalloc(uint16_t length, uint8_t blockSize)
{
    uint8_t* rPointer = bitmalloc(length * blockSize);
    for(uint16_t i = 0; i < (length * blockSize); i++)
    {
        rPointer[i] = 0;
    }
    return (void*)rPointer;
}

void bitfree(void* ptr, uint16_t size)
{
    uint32_t pointerPos = (uint32_t)((uint8_t*)ptr-(uint8_t*)arena);
    uint16_t byteIndex = pointerPos/8;
    uint8_t bitIndex = pointerPos%8;
    for(int i = 0; i < size; i++)
    {
        setbit(&bitmap[byteIndex], bitIndex, FREE);
        bitIndex++;
        if(bitIndex>7)
        {
            byteIndex++;
            bitIndex = 0;
        }
    }
}