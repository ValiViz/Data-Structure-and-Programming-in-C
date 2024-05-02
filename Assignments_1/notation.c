#include <stdio.h>
#include <string.h>
#define MAX_SIZE 10000

char str[MAX_SIZE];

int main()
{
    gets(str);
    char *dot = strstr(str, ".");
    int len = strlen(str);
    if (dot == NULL)
        dot = str + len;

    int sign = 1;
    if (str[0] == '-')
    {
        str[0] = 0;
        sign = -1;
    }

    char *top, *bottom, *now;
    for (top = str; *top == '0' || *top == '.'; top++)
        ;
    printf("%c", *top);

    for (bottom = str + len - 1; *bottom == '0' || *bottom == '.'; bottom--)
        ;
    if (bottom > top)
    {
        printf(".");
        for (now = top + 1; now <= bottom; now++)
        {
            if (*now != '.')
            {
                printf("%c", *now);
            }
        }
    }

    if (dot > top)
        printf("e%d", dot - top - 1);
    else
        printf("e%d", dot - top);

    return 0;
}