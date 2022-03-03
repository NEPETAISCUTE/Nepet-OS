#include "string.h"

void itoa(char* s, int num)
{
    if(num<0)
    {
        *s='-';
        s++;
        num*=-1;
    }
    int temp = num;
    int cntLen = 0;
    while(temp>1)
    {
        temp/=10;
        cntLen++;
    }
    for(unsigned int i = 0; i < cntLen; i++)
    {
        s[cntLen-i-1] = '0'+num%10;
        num /= 10;
    }
    s[cntLen] = '\0';
}

int atoi(char* s)
{
    int val = 0;
    size_t length = strlen(s);
    unsigned char neg = 0;
    if(s[0]=='-')
    {
        neg = 1;
        s++;
        length--;
    }
    for(unsigned int i = 0; i < length; i++)
    {
        val *= 10;
        val += (s[i]-'0');
    }
    if(neg)
        val*=-1;
    return val;
}

size_t strlen(char* s)
{
    size_t length = 0;
    while(*(s+length))
        length++;
    return length;
}