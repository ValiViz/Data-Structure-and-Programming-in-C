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

// 结构（体）类型的关键字：struct
// 结构（体）类型：struct student / STUDENT
// 结构类型名/结构体名：student
// （结构）成员名：name
// 结构（体）类型变量（名）：LiHua