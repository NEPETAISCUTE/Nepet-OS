#include "string.h"

#ifdef S_DEBUG
#include <stdio.h>
int main()
{
    char string[20];
    itohex(string, 0x7e538);
    printf("%d\n",strlen(string));
    printf("%s\n",string);
}
#endif

void concat(char* s, const char* Sadd)
{
    size_t ssize = strlen(s);

    strcpy(&s[ssize], Sadd, strlen(Sadd));
    s[ssize+strlen(Sadd)] = '\0';
}

void itohex(char* s, uint64_t num)
{
    uint64_t temp = num;
    unsigned int cntLen = 0;
    while(temp>=1)
    {
        temp /= 16;
        cntLen++;
    }
    if(cntLen==0)
        cntLen++;

    for(unsigned int i = 0; i < cntLen; i++)
    {
        if(num%16<10)
            s[cntLen-i-1] = '0'+num%16;
        else
            s[cntLen-i-1] = 'A'+num%16-10;
        num /= 16;
    }
    s[cntLen] = '\0';
}

void itoa(char* s, int num)
{
    //just takes care of negative numbers
    if(num<0)
    {
        *s = '-';
        s++;
        num *= -1;
    }

    //get the length of the future string into cntLen
    int temp = num;
    unsigned int cntLen = 0;
    while(temp>=1)
    {
        temp /= 10;
        cntLen++;
    }
    if(cntLen==0)
        cntLen++;

    //proceed to write the text into the string
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

void strcpy(char* dest, const char* src, size_t maxLen)
{
    for(int i = 0; i < maxLen; i++)
    {
        if(src[i]=='\0')
            break;
        dest[i]=src[i];
    }
}

size_t strlen(char* s)
{
    size_t length = 0;
    while(*(s+length))
        length++;
    return length;
}