#include <stdio.h>

int main()
{
    char str[1000];
    while(gets(str) != NULL)
    {
        puts(str);
    }
    return 0;
}