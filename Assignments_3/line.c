#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;

typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
    int count;
} ElemType;

// int compar(const void *Ea, const void *Eb)
// {
//     ElemType ea = *(ElemType *)Ea, eb = *(ElemType *)Eb;
//     （注意替换）
// }

// Status visit(ElemType *E)
// {
//     （注意替换）
//     return OK;
// }

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

int LocateElem(const SqList *L, const ElemType *E, int (*compar)(const void *, const void *))
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

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    for (int i = 0; i < L->length; i++)
        if (!func_visit(&L->data[i]))
            return ERROR;
    return OK;
}

// Status unionL(SqList *desk, const SqList *src)
// {
//     ElemType e;
//     for (int i = 0; i < src->length; i++)
//     {
//         GetElem(src, i, &e);
//         if (!LocateElem(desk, &e, compar))
//             if (!ListInsert(desk, desk->length, &e))
//                 return ERROR;
//         return OK;
//     }
// }

Status CanBeConnected(const ElemType *A, const ElemType *B)
{
    return A->x2 == B->x1 && A->y2 == B->y1;
}

Status Connect(ElemType *A, ElemType *B)
{
    A->x2 = B->x2;
    A->y2 = B->y2;
    A->count += B->count;
    return OK;
}

Status DulConnect(ElemType *A, ElemType *B)
{
    A->x1 = B->x1;
    A->y1 = B->y1;
    A->count += B->count;
    return OK;
}

int main()
{
    SqList Line;
    ElemType a;
    scanf("%d", &Line.length);
    for (int i = 0; i < Line.length; i++)
    {
        scanf("%d%d%d%d", &Line.data[i].x1, &Line.data[i].y1, &Line.data[i].x2, &Line.data[i].y2);
        Line.data[i].count = 1;
    }

    for (int i = 0; i < Line.length; i++)
    {
        for (int j = 0; j < Line.length; j++)
        {
            if (CanBeConnected(&Line.data[i], &Line.data[j]))
            {
                Connect(&Line.data[i], &Line.data[j]);
                ListDelete(&Line, j, &a);
                if (i > j)
                    i--;
                j--;
            }
            else if (CanBeConnected(&Line.data[j], &Line.data[i]))
            {
                DulConnect(&Line.data[i], &Line.data[j]);
                ListDelete(&Line, j, &a);
                if (i > j)
                    i--;
                j--;
            }
        }
    }

    int flag = 0;
    for (int i = 0; i < Line.length; i++)
    {
        flag = Line.data[i].count > Line.data[flag].count ? i : flag;
    }

    printf("%d %d %d\n", Line.data[flag].count, Line.data[flag].x1, Line.data[flag].y1);

    return 0;
}