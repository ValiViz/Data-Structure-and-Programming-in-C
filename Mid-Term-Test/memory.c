#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 110
typedef int Status;

typedef struct
{
    int site;
    int memory;
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

typedef struct DulNode
{
    ElemType data;
    struct DulNode *next;
    struct DulNode *prior;
} DulNode;

typedef struct
{
    int length;
    DulNode *head;
} DulLinkList;

Status InitList(DulLinkList *L)
{
    L->length = 0;
    L->head = (DulNode *)malloc(sizeof(DulNode));
    L->head->next = L->head;
    L->head->prior = NULL;
    return OK;
}

Status ListEmpty(const DulLinkList *L)
{
    if (!L->length)
        return FALSE;
    return TRUE;
}

Status ClearList(DulLinkList *L)
{
    InitList(L);
    return OK;
}

Status GetElem(const DulLinkList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    DulNode *now = L->head->next;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    *E = now->data;
    return OK;
}

int LocateElem(const DulLinkList *L, const ElemType *E, int (*func_compar)(const void *, const void *))
{
    DulNode *now = L->head;
    for (int i = 0; i < L->length; i++)
    {
        now = now->next;
        if (func_compar(&now->data, E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(DulLinkList *L, int i, const ElemType *E)
{
    if (i > L->length || i < 0)
        return ERROR;
    DulNode *now = L->head;
    if (L->length == 0)
    {
        now->next = (DulNode *)malloc(sizeof(DulNode));
        now->next->next = now->next->prior = now->next;
        now->next->data = *E;
        L->length++;
        return OK;
    }
    if (i > 0 && i == L->length)
        now = now->next->prior;
    else
        for (int j = 0; j < i; j++)
        {
            now = now->next;
        }
    DulNode *tmp = now->next;
    now->next = (DulNode *)malloc(sizeof(DulNode));
    now->next->next = tmp;
    now->next->prior = tmp->prior;
    tmp->prior = now->next;
    now->next->data = *E;
    L->length++;
    return OK;
}

Status ListDelete(DulLinkList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0)
        return ERROR;
    DulNode *now = L->head;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    DulNode *tmp = now->next;
    now->next = tmp->next;
    tmp->next->prior = tmp->prior;
    *E = tmp->data;
    free(tmp);
    L->length--;
    return OK;
}

int ListLength(const DulLinkList *L)
{
    return L->length;
}

Status ListTraverse(DulLinkList *L, DulNode **N, Status (*func_visit)(DulNode *, int), int m)
{
    DulNode *now = *N;
    for (int i = 0; i < L->length; i++)
    {
        if (func_visit(now, m))
        {
            *N = now;
            return OK;
        }
        else
            now = now->next;
    }
    return ERROR;
}

Status unionL(DulLinkList *desk, const DulLinkList *src, int (*func_compar)(const void *, const void *))
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

Status OccupyAble(DulNode *N, int m)
{
    if (N->data.memory >= m)
    {
        return TRUE;
    }
    return FALSE;
}

Status NodePrint(DulNode *N, int m)
{
    if (N->data.memory > 0)
        printf("%d %d\n", N->data.site, N->data.memory);
    return 0;
}

Status ListSearch(DulNode **N, int m)
{
    DulNode *now = *N;
    DulNode *goal = NULL;
    int min;
    do
    {
        if (OccupyAble(now, m))
        {
            min = now->data.memory;
            goal = now;
            now = now->next;
            break;
        }
        now = now->next;
    } while (now != *N);
    // 比起作业原题代码唯一修改了的地方：注释掉了下面这一段
    // while (now != *N)
    // {
    //     if (now->data.memory < min && OccupyAble(now, m))
    //     {
    //         min = now->data.memory;
    //         goal = now;
    //     }
    //     now = now->next;
    // }
    if (goal != NULL)
    {
        *N = goal;
        goal->data.memory -= m;
    }
    return ERROR;
}

int main()
{
    int N;
    scanf("%d", &N);
    DulLinkList List;
    InitList(&List);
    ElemType input;
    while (N--)
    {
        scanf("%d %d", &input.site, &input.memory);
        ListInsert(&List, List.length, &input);
    }

    int m;
    DulNode *now = List.head->next;
    scanf("%d", &m);
    while (m != -1)
    {
        ListSearch(&now, m);
        scanf("%d", &m);
    }

    ListTraverse(&List, &now, NodePrint, 0);

    return 0;
}