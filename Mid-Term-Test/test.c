#include <stdio.h>

struct st
{

    char name[20];

    int score;
};

int main()

{
    int a[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, *p;

    p = a + 5;

    printf("%d ", *p++);

    printf("%d", *p--);
    return 0;
}