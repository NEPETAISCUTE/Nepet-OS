#include "string.h"

#ifdef S_DEBUG
#include <stdio.h>
int main()
{
    char string[20];
    itoa(string,-38462);
    printf("%d\n",strlen(string));
    printf("%s\n",string);
}
#endif

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
    while(temp>1)
    {
        temp /= 10;
        cntLen++;
    }

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

size_t strlen(char* s)
{
    size_t length = 0;
    while(*(s+length))
        length++;
    return length;
}