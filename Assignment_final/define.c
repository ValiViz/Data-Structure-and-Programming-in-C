#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int max(int a, int b)
{
    if(a > b)return a;
    return b;
}
int main()
{
    FILE *IN = fopen("words.txt", "r");
    FILE *OUT = fopen("def.txt", "w");
    char str[20];
    int len = 0;
    fprintf(OUT, "char keepwords[165][10] = {");
    int count = 0;
    while(fgets(str, 19, IN) != NULL)
    {
        int p = strlen(str) - 1;
        str[p] = '\0';
        fprintf(OUT, "\"%s\", ", str);
        if(strlen(str) >= 10)
        printf("%d\n", count);
        count++;
    }
    printf("%d", len);
}