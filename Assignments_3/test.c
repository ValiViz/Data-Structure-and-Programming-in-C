#include <stdio.h>
#include <math.h>

int main()
{
    int (*ptr)[3][4];
    int a[3][4];
    for(int i = 0; i < 12; i++)
    {
        a[i/4][i%4] = 10 * (i / 4) + i % 4;
    }
    ptr = &a;
    printf("%d", (*ptr)[2][3]);
}