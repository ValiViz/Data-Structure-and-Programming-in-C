#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define REP(i, a, b) for (register int i = a; i <= b; i++)
#define PER(i, a, b) for (register int i = a; i >= b, i--)
typedef long long LL;
struct test
{
    int id;
    char name[20];
    int machine;
    char time[7];
    int mark;
} a[205], b[205];
int main()
{
    int n, i, j, k = 0, m;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %s %d %s", &a[i].id, &a[i].name, &a[i].machine, &a[i].time);
        a[i].mark = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i].id == a[j].id && a[i].machine != a[j].machine && a[i].mark != 0)
            {
                b[k].id = a[i].id;
                strcpy(b[k++].name, a[i].name);
                for (m = i + 1; m < n; m++)
                {
                    if (a[m].id == a[i].id)
                    {
                        a[m].mark = 1;
                    }
                    break;
                }
                break;
            }
        }
    }
    int temp;
    char c[20];
    for (i = 0; i < k - 1; i++)
    {
        int count = 0;
        for (j = 0; j < k - 1 - i; j++)
        {
            if (b[j].id > b[j + 1].id)
            {
                temp = b[j].id;
                b[j].id = b[j + 1].id;
                b[j + 1].id = temp;
                strcpy(c, b[j].name);
                strcpy(b[j].name, b[j + 1].name);
                strcpy(b[j + 1].name, c);
                count = 1;
            }
        }
        if (count == 0)
        {
            break;
        }
    }
    for (i = 0; i < k; i++)
    {
        printf("%d %s\n", b[i].id, b[i].name);
    }
}