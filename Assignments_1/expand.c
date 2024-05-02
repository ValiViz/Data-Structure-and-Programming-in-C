#include <stdio.h>
#include <stdlib.h>

int sort(char c)
{
    if(c>='a'&&c<='z') return 1;
    if(c>='A'&&c<='Z') return 2;
    if(c>='0'&&c<='9') return 3;
    return 0;
}

int main()
{
    char last, now, next;
    last=getchar();
    printf("%c", last);
    while((now = getchar()) != EOF)
    {
        if(now!='-')
        {
            printf("%c", now);
            last = now;
        }
        else
        {
            if((next = getchar()) !=EOF)
            {
                if(sort(last)&&sort(last)==sort(next)&&next>last)
                {
                    for(char ch = last + 1; ch <= next; ch++)
                    {
                        printf("%c", ch);
                    }
                    last = next;
                }
                else
                {
                    printf("-%c", next);
                }
            }
            else
            {
                printf("-");
            }
        }
    }

    return 0;
}