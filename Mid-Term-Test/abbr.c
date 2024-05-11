#include <stdio.h>
#include <string.h>

char str[500];

char *work(char *p)
{
    if (*p == '\n')
        return p;
    if (*(p + 1) == *p + 1)
    {
        if (*(p + 2) == *(p + 1) + 1 && *(p + 2) != '\n')
        {
            printf("%c-", *p);
            p = p + 2;
            while (*(p + 1) == *p + 1)
            {
                p++;
            }
            printf("%c", *p);
            return p;
        }
    }
    printf("%c", *p);
    return p;
}

int main()
{
    gets(str);
    char *p = str;
    int length = strlen(str);
    for (; p + 2 < str + length; p++)
    {
        p = work(p);
    }
    return 0;
}