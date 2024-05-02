/*
去除重复字母
补全未出现字母
*/

#include <stdio.h>

char str[27];
int exist[27] = {};

int main()
{
    FILE *IN, *OUT;
    if ((IN = fopen("encrypt.txt", "r")) == NULL)
    {
       printf("Can&rsquo;t open in.txt!");
    }
    OUT = fopen("output.txt", "w");

    char c;
    char *p = str;
    while ((c = getchar()) != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            if (exist[c - 'a']) continue;
            exist[c - 'a']++;
            *(p++) = c;
        }
    }
    for (c = 'z'; c >= 'a'; c--)
    {
        if (!exist[c - 'a']) *(p++) = c;
    }

    while ((c = fgetc(IN)) != EOF)
    {
        if (c >= 'a' && c <= 'z') fputc(str[c - 'a'], OUT);
        else fputc(c, OUT);
    }

    fclose(IN);
    fclose(OUT);

    return 0;
}