#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000

char *replace(char *src, int len, char *desk)
{
    char tmp[MAXSIZE];
    strcpy(tmp, src + len);
    int len_new = strlen(desk);
    strcpy(src, desk);
    strcat(src, tmp);
}

int riselen(char *p)
{
    int ans = 1;
    while (*(p + 1) != '\0')
    {
        if (*(p + 1) == *p + 1)
        {
            ans++;
            p++;
        }
        else
        {
            break;
        }
    }
    return ans;
}

int main()
{
    char str[MAXSIZE];
    gets(str);
    int len = strlen(str);
    char src[10] = "";
    char *p = str;
    for (int i = 0; i < len; i++)
    {
        int new = riselen(p);
        if (new > 2)
        {
            src[0] = *p;
            src[1] = '-';
            src[2] = *p + new - 1;
            printf("%s", src);
            i += new - 1;
            p += new - 1;
        }
        else
        {
            putchar(*p);
        }
        p++;
    }
}