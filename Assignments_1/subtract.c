#include <stdio.h>
#include <string.h>

char str[81], num1[81], num2[81], res[81] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";

void work(char a[], char b[])
{
    for(int i = 80; i >= 0; i--)
    {
        if(a[i] >= b[i])
        {
            res[i] = a[i] - b[i] + '0';
        }
        else
        {
            a[i - 1]--;
            res[i] = a[i] + 10 - b[i] + '0';
        }
    }
    if(strcmp(res, "000000000000000000000000000000000000000000000000000000000000000000000000000000000") == 0)
    {
        puts("0");
        return;
    }
    int i;
    for(i = 0; i < 81 && res[i] == '0'; i++)
        ;
    puts(&res[i]);
    return;
}

int main()
{
    gets(str);
    int len1 = strlen(str);
    for(int i = 0; i < 81 - len1; i++)
    {
        strcpy(num1, res);
    }
    for(int i = 0; i < len1; i++)
    {
        strcpy(&num1[81 - len1], str);
    }

    gets(str);
    int len2 = strlen(str);
    for(int i = 0; i < 81 - len2; i++)
    {
        strcpy(num2, res);
    }
    for(int i = 0; i < len2; i++)
    {
        strcpy(&num2[81 - len2], str);
    }

    if(strcmp(num1, num2)<0)
    {
        printf("-");
        work(num2, num1);
    }
    else
    {
        work(num1, num2);
    }

    return 0;
}