#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char type;
    int num;
    double time;
    int count;
} STUDENT;
STUDENT list[10000];
int N = 0;

int search(STUDENT *S)
{
    int i = 0;
    for (i = 0; i < N; i++)
    {
        if (S->num == list[i].num)
        {
            if (S->type == list[i].type)
            {
                break;
            }
        }
    }
    return i;
}
int second(int h, int m, int s)
{
    return 3600 * h + 60 * m + s;
}
double vert(int h1, int m1, int s1, int h2, int m2, int s2)
{
    int time = second(h2, m2, s2) - second(h1, m1, s1);
    double ans = (double)time / 3600;
    return ans;
}
int cmp(const void *a, const void *b)
{
    STUDENT *A = (STUDENT *)a, *B = (STUDENT *)b;
    if (A->time - B->time < 0)
        return -1;
    return 1;
}
int main()
{
    int m;
    STUDENT tmp;
    int h1, m1, s1, h2, m2, s2;
    scanf("%d", &m);
    while (m--)
    {
        char x = '\n';
        while (x == '\n')
            x = getchar();
        tmp.type = x;
        scanf("%d%d%d%d%d%d%d", &tmp.num, &h1, &m1, &s1, &h2, &m2, &s2);
        tmp.count = 1;
        tmp.time = vert(h1, m1, s1, h2, m2, s2);
        int poi = search(&tmp);
        if (poi == N)
        {
            list[poi] = tmp;
            N++;
        }
        else
        {
            list[poi].count++;
            list[poi].time += tmp.time;
        }
    }
    qsort(list, N, sizeof(STUDENT), cmp);

    for (int i = 0; i < N; i++)
    {
        if (list[i].type == 'B')
            printf("%c%d %.2lf %d\n", list[i].type, list[i].num, list[i].time, list[i].count);
    }
    for (int i = 0; i < N; i++)
    {
        if (list[i].type == 'M')
            printf("%c%d %.2lf %d\n", list[i].type, list[i].num, list[i].time, list[i].count);
    }
    for (int i = 0; i < N; i++)
    {
        if (list[i].type == 'D')
            printf("%c%d %.2lf %d\n", list[i].type, list[i].num, list[i].time, list[i].count);
    }
}