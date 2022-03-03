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
    for(uint i = 0; i < cntLen; i++)
    {
        s[cntLen-i-1] = '0'+num%10;
        num /= 10;
    }
    s[cntLen] = '\0';
}

int atoi(char* s)
{
    int val = 0;
    uint length = strlen(s);
    ubyte neg = 0;
    if(s[0]=='-')
    {
        neg = 1;
        s++;
        length--;
    }
    for(uint i = 0; i < length; i++)
    {
        val *= 10;
        val += (s[i]-'0');
    }
    if(neg)
        val*=-1;
    return val;
}

uint strlen(char* s)
{
    uint length = 0;
    while(*(s+length))
        length++;
    return length;
}