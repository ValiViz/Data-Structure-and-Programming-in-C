/*
小型图书管理系统
【问题描述】
小明同学特别喜欢买书看书。由于书较多，摆放杂乱，找起来非常麻烦。这学期小明同学上了数据结构与程序设计课后，决定改变这种状况：用C开发一个小型图书管理系统。系统中包含的图书信息有：书名、作者、出版社、出版日期等。首先，图书管理系统对已有的书（原始书库，存放在一个文本文件中）按书名字典序进行（按书名中各字符的ASCII码值由小到大排序）摆放（即将原始无序的图书信息文件生成一个有序的文件，即新书库），以便查找。该管理系统可以对新书库中图书条目进行如下操作：
1.录入。新增书录入到书库中（即从输入中读入一条图书信息插入到已排序好的图按书文件相关位置处）
2.查找。按书名或书名中关键字信息在书库中查找相关图书信息，若有多本书，按字典序输出。
3.删除。输入书名或书名中关键字信息，从书库中查找到相关书并将其删除，并更新书库。
【输入形式】
原始的图书信息（原始书库）保存在当前目录下的books.txt中。
用户操作从控制台读入，首先输入操作功能序号（1代表录入操作，2代表查找操作，3代表删除操作，0代表将已更新的图书信息保存到书库中并退出程序），然后在下一行输入相应的操作信息（录入操作后要输入一条图书信息，查找和删除操作后只要输入书名或书名中部分信息）。程序执行过程中可以进行多次操作，直到退出（输入操作0）程序。
要求：
1、原始文件中的图书信息与录入的图书信息格式相同，每条图书信息都在一行上，包括书名（不超过50个字符）、作者（不超过20个字符）、出版社（不超过30个字符）和出版日期（不超过10个字符），只由英文字母和下划线组成，用一个空格分隔。图书信息总条数不会超过500.
2、下划线字符参加排序。
3、图书不会重名。
【输出形式】
进行录入和删除操作，系统会更新图书信息，但不会在控制台窗口显示任何信息。
进行查找操作后，将在控制台按书名字典序分行输出查找到的图书信息，书名占50个字符宽度，作者占20个字符宽度，出版社占30个字符宽度，出版日期占10个字符宽度，都靠左对齐输出。
最终按字典排序的图书信息保存在当前目录下的ordered.txt中，每条图书信息占一行，格式与查找输出的图书信息相同。
【样例输入】
假设books.txt中保存的原始图书信息为：
The_C_programming_language Kernighan Prentice_Hall 1988
Programming_in_C Yin_Bao_Lin China_Machine_Press 2013
Data_structures_and_Algorithm_Analysis_in_C Mark_Allen_Weiss Addison_Wesley 1997
ANSI_and_ISO_Standard_c Plauger Microsoft_Press 1992
Data_structures_and_program_design_in_C Robert_Kruse Pearson_Education 1997
Computer_network_architectures Anton_Meijer Computer_Science_Press 1983
C_programming_guidelines Thomas_Plum Prentice_Hall 1984
Data_structures_using_C Tenenbaum Prentice_Hall 1990
Operating_system_concepts Peterson Addison_Wesley 1983
Computer_networks_and_internets Douglas_E_Come Electronic_Industry 2017
用户控制台输入信息为：
1
Data_structures_and_C_programs Christopher Addison_Wesley 1988
2
structure
1
The_C_programming_tutor Leon_A_Wortman R_J_Brady 1984
2
rogram
3
rogramming
0
【样例输出】
用户输入“2 structure”后，控制台输出：

1.jpg

用户输入“2 rogram”后，控制台输出：

2.jpg

ordered.txt文件内容为：
3.jpg

【样例说明】
先读入books.txt中的10条图书信息，按照书名进行字典序排序；用户进行了五次操作，然后退出：第一次操作是插入了一条图书信息，这时有11条图书信息，按书名字典序排序为：
ANSI_and_ISO_Standard_c Plauger Microsoft_Press 1992
C_programming_guidelines Thomas_Plum Prentice_Hall 1984
Computer_network_architectures Anton_Meijer Computer_Science_Press 1983
Computer_networks_and_internets Douglas_E_Come Electronic_Industry 2017
Data_structures_and_Algorithm_Analysis_in_C Mark_Allen_Weiss Addison_Wesley 1997
Data_structures_and_C_programs Christopher Addison_Wesley 1988
Data_structures_and_program_design_in_C Robert_Kruse Pearson_Education 1997
Data_structures_using_C Tenenbaum Prentice_Hall 1990
Operating_system_concepts Peterson Addison_Wesley 1983
Programming_in_C Yin_Bao_Lin China_Machine_Press 2013
The_C_programming_language Kernighan Prentice_Hall 1988
第二次操作是查找书名包含structure的图书，有4本图书信息按照格式要求输出到屏幕；第三次操作又插入了一条图书信息，这时有12条图书信息；第四次操作查找书名包含rogram的图书，有6本图书信息按照格式要求输出到屏幕；第五次操作是删除书名包含rogramming的图书信息，有四条图书信息要删除，剩下八条图书信息；最后退出程序前将剩余的八条图书信息按照格式要求存储在ordered.txt文件中。
【评分标准】

该程序要求编写图书管理系统。提交程序文件名为books.c。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000

typedef struct
{
    char title[51];
    char author[21];
    char publish[31];
    char date[11];
} ElemType;

typedef int Status;

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

Status BookPrint(const ElemType *E)
{
    printf("%-50s%-20s%-30s%-10s\n", E->title, E->author, E->publish, E->date);
    return OK;
}

Status BookFPrint(FILE *File, const ElemType *E)
{
    fprintf(File, "%-50s%-20s%-30s%-10s\n", E->title, E->author, E->publish, E->date);
    return OK;
}

Status BookSearch(const char *str, ElemType *E)
{
    if (strstr(E->title, str) != NULL)
        return TRUE;
    else
        return ERROR;
}

Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status ListEmpty(const SqList *L)
{
    if (L->length == 0)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status GetElem(const SqList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    *E = L->data[i];
    return OK;
}

int compar(const void *Ea, const void *Eb)
{
    ElemType Booka = *(ElemType *)Ea, Bookb = *(ElemType *)Eb;
    return strcmp(Booka.title, Bookb.title);
}

int LocateElem(const SqList *L, const ElemType *E, int (*compar)(const ElemType *, const ElemType *))
{
    for (int i = 0; i < L->length; i++)
    {
        if (compar(&L->data[i], E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(SqList *L, int i, const ElemType *E)
{

    if (i > L->length || i < 0 || L->length >= MAXSIZE)
        return ERROR;
    for (int j = L->length; j > i; j--)
        L->data[j] = L->data[j - 1];
    L->data[i] = *E;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0 || L->length <= 0)
        return ERROR;
    *E = L->data[i];
    L->length--;
    for (; i < L->length; i++)
    {
        L->data[i] = L->data[i + 1];
    }
    return OK;
}

int ListLength(const SqList *L)
{
    return L->length;
}

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *E))
{
    if (L->length <= 0)
        return ERROR;
    for (int i = 0; i < L->length; i++)
        if (!func_visit(&L->data[i]))
            return ERROR;
    return OK;
}

Status unionL(SqList *desk, const SqList *src)
{
    ElemType e;
    for (int i = 0; i < src->length; i++)
    {
        GetElem(src, i, &e);
        if (!LocateElem(desk, &e, compar))
            if (!ListInsert(desk, desk->length, &e))
                return ERROR;
        return OK;
    }
}

int main()
{
    FILE *file = NULL;
    file = fopen("books.txt", "r");
    SqList BookList;
    ElemType Book;
    char info[121];
    InitList(&BookList);

    while (fgets(info, 120, file) != NULL)
    {
        sscanf(info, "%s%s%s%s", &Book.title, &Book.author, &Book.publish, &Book.date);
        ListInsert(&BookList, BookList.length, &Book);
    }

    int num;
    while (gets(info) != NULL)
    {
        switch (info[0] - '0')
        {
        case 0:
            fclose(file);
            qsort(BookList.data, BookList.length, sizeof(ElemType), compar);
            file = fopen("ordered.txt", "w");
            for (int i = 0; i < BookList.length; i++)
                BookFPrint(file, &BookList.data[i]);
            fclose(file);
            return 0;
        case 1:
            gets(info);
            sscanf(info, "%s%s%s%s", &Book.title, &Book.author, &Book.publish, &Book.date);
            ListInsert(&BookList, BookList.length, &Book);
            qsort(BookList.data, BookList.length, sizeof(ElemType), compar);
            break;
        case 2:
            gets(info);
            for (int i = 0; i < BookList.length; i++)
                if (BookSearch(info, &BookList.data[i]) == TRUE)
                    BookPrint(&BookList.data[i]);
            break;
        case 3:
            gets(info);
            for (int i = 0; i < BookList.length; i++)
                if (BookSearch(info, &BookList.data[i]) == TRUE)
                {
                    ListDelete(&BookList, i, &Book);
                    BookPrint(&Book);
                    i--;
                }
        }
    }
}