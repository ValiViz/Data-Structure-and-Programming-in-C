#include <stdio.h>
#include <string.h>

char str[100] = "";

struct num{
    int it;
    struct num *next;
}

work(int n, struct num *x)
{
    struct num *now = x;
    char str_now[5];
    if(n > 1)
    {
        struct num *tmp = now;
        for(int i = 0; i < n; i++)
        {
            now = now -> next;
            tmp -> next = now -> next;
            sprintf(str_now, "%d ", now -> it);
            strcat(str, str_now);
            work(n-1, x);
            int a = strlen(str), b = strlen(str_now);
            str[a - b] = '\0';
            tmp -> next = now;
            tmp = now;
        }
    }
    else
    {
        now = now -> next;
        sprintf(str_now, "%d ", now -> it);
        strcat(str, str_now);
        puts(str);
        int a = strlen(str), b = strlen(str_now);
        str[a - b] = '\0';
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    struct num x[12];

    for(int i = 0; i <= N; i++)
    {
        x[i].it = i;
        x[i].next = &x[i+1];
    }

    work(N, x);
}