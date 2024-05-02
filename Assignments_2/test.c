#include <stdio.h>
#include <string.h>


int main()
{
    FILE *fp = fopen("books.txt", "r+");
    char str[100];
    fgets(str, 100, fp);
    char *a = str;
    fseek(fp, 0, SEEK_CUR);
    fputs(a, fp);
    fputs(a, fp);
    fclose(fp);
    return 0;
}