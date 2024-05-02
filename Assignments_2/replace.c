#include <stdio.h>
#include <string.h>
#include <ctype.h>

void str_replace(char *desk, int top, int len, char *to)
{
    char tmp[1000];
    strcpy(tmp, to);
    strcat(tmp, (desk + top + len));
    *(desk + top) = '\0';
    desk = strcat(desk, tmp);
    return;
}

int same(char a, char b)
{
    return tolower(a) == tolower(b);
}

int main()
{
    FILE *IN, *OUT;
    if((IN = fopen("filein.txt", "r")) == NULL)
    {
       printf("Can&rsquo;t open in.txt!");
    }
    OUT = fopen("fileout.txt", "w");

    char str[1000], from[1000], to[1000];
    gets(from);
    int from_len = strlen(from);
    gets(to);
    int to_len = strlen(to);

    char *top, *now;
    while(fgets(str, 1000, IN) != NULL)
    {
        int str_len = strlen(str);
        now = str;
        for(int i = 0; i < str_len; i++)
        {
            int j;
            for(j = 0; j < from_len && same(str[i + j], from[j]); j++);
            if(j == from_len)
            {
                str_replace(str, i, from_len, to);
                i += to_len;
            }
            
        }
        fputs(str, OUT);
    }

    fclose(IN);
    fclose(OUT);

    return 0;
}