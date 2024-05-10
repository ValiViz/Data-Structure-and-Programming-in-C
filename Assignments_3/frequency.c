/*
	词频统计（数组或链表实现）
【问题描述】

编写程序统计一个英文文本文件中每个单词的出现次数（词频统计），并将统计结果按单词字典序输出到屏幕上。

注：在此单词为仅由字母组成的字符序列。包含大写字母的单词应将大写字母转换为小写字母后统计。

【输入形式】

打开当前目录下文件“article.txt”，从中读取英文单词进行词频统计。


【输出形式】

程序将单词统计结果按单词字典序输出到屏幕上，每行输出一个单词及其出现次数，单词和其出现次数间由一个空格分隔，出现次数后无空格，直接为回车。

【样例输入】

当前目录下文件article.txt内容如下：


“Do not take to heart every thing you hear.”

“Do not spend all that you have.”

“Do not sleep as long as you want;”


【样例输出】

all 1

as 2

do 3

every 1

have 1

hear 1

heart 1

long 1

not 3

sleep 1

spend 1

take 1

that 1

thing 1

to 1

want 1

you 3


【样例说明】

按单词字典序依次输出单词及其出现次数。


【评分标准】

通过所有测试点将得满分。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000
typedef int Status;

typedef struct
{
    char data[16];
    int count;
} ElemType;

int compar(const void *Ea, const void *Eb)
{
    ElemType ea = *(ElemType *)Ea, eb = *(ElemType *)Eb;
    return strcmp(ea.data, eb.data);
}

Status ElemPrint(ElemType *E)
{
    printf("%s %d\n", E->data, E->count);
    return OK;
}

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

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

int LocateElem(const SqList *L, const ElemType *E, int (*func_compar)(const void *, const void *))
{
    for (int i = 0; i < L->length; i++)
    {
        if (func_compar(&L->data[i], E) == 0)
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

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    for (int i = 0; i < L->length; i++)
        if (!func_visit(&L->data[i]))
            return ERROR;
    return OK;
}

Status unionL(SqList *desk, const SqList *src, int (*func_compar)(const void *, const void *))
{
    ElemType e;
    for (int i = 0; i < src->length; i++)
    {
        GetElem(src, i, &e);
        if (!LocateElem(desk, &e, func_compar))
            if (!ListInsert(desk, desk->length, &e))
                return ERROR;
        return OK;
    }
}


Status strinsert(SqList *L, char *str)
{
    if(*str == '\0') return ERROR;
    ElemType word;
    strcpy(word.data, str);
    word.count = 1;
    int goal = LocateElem(L, &word, compar);
    if(goal != -1)
    {
        L->data[goal].count++;
    }
    else
    {
        ListInsert(L, L->length, &word);
    }
}

char *strprocess(SqList *L, char *str)
{
    char *p = str;
    while (*p != '\0')
    {
        if(*p >= 'a' && *p <= 'z')
        {
            p++;
        }
        else if(*p >= 'A' && *p <= 'Z')
        {
            *p += 'a' - 'A';
            p++;
        }
        else
        {
            *p = '\0';
            strinsert(L, str);
            strprocess(L, p + 1);
            return str;
        }
    }
    strinsert(L, str);
    return str;
}

int main()
{
    SqList List;
    InitList(&List);
    char str[100];
    FILE *IN = fopen("article.txt", "r");
    while(fscanf(IN, "%s", str) != EOF)
    {
        strprocess(&List, str);
    }
    qsort(List.data, List.length, sizeof(ElemType), compar);
    ListTraverse(&List, ElemPrint);
    fclose(IN);
    return 0;
}