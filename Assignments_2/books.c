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