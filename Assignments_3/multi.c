#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;

typedef struct
{
    int coefficient;
    int exponent;
} ElemType;

int compar(const void *Ea, const void *Eb)
{
    ElemType ea = *(ElemType *)Ea, eb = *(ElemType *)Eb;
    return ea.exponent - eb.exponent;
}

Status ElemPrint(ElemType *E)
{
    if (E->coefficient != 0)
        printf("%d %d ", E->coefficient, E->exponent);
    return OK;
}

Status ElemAdd(ElemType *desk, const ElemType *src)
{
    desk->coefficient += src->coefficient;
    return OK;
}

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct
{
    int length;
    Node *head;
    Node *rear;
} LinkList;

Status InitList(LinkList *L)
{
    L->length = 0;
    L->head = (Node *)malloc(sizeof(Node));
    L->head->next = NULL;
    L->rear = NULL;
    return OK;
}

Status ListEmpty(const LinkList *L)
{
    if (!L->length)
        return FALSE;
    return TRUE;
}

Status ClearList(LinkList *L)
{
    InitList(L);
    return OK;
}

Status GetElem(const LinkList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    Node *now = L->head->next;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    *E = now->data;
    return OK;
}

int LocateElem(const LinkList *L, const ElemType *E, int (*compar)(const void *, const void *))
{
    Node *now = L->head;
    for (int i = 0; i < L->length; i++)
    {
        now = now->next;
        if (compar(&now->data, E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(LinkList *L, int i, const ElemType *E)
{
    if (i > L->length || i < 0)
        return ERROR;
    Node *now = L->head;
    if (i > 0 && i == L->length)
        now = L->rear;
    else
        for (int j = 0; j < i; j++)
        {
            now = now->next;
        }
    Node *tmp = now->next;
    now->next = (Node *)malloc(sizeof(Node));
    now->next->data = *E;
    if (i == L->length)
        L->rear = now->next;
    now->next->next = tmp;
    L->length++;
    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0)
        return ERROR;
    Node *now = L->head;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    if (i == L->length - 1)
        L->rear = now;
    Node *tmp = now->next;
    now->next = now->next->next;
    *E = tmp->data;
    free(tmp);
    L->length--;
    return OK;
}

int ListLength(const LinkList *L)
{
    return L->length;
}

Status ListTraverse(LinkList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    Node *now = L->head;
    for (int i = 0; i < L->length; i++)
    {
        now = now->next;
        if (!func_visit(&now->data))
            return ERROR;
    }
    return OK;
}

Status unionL(LinkList *desk, const LinkList *src)
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
    ElemType A[100], B[100], result = {0, 0};
    char c = 32;
    int N_A, N_B;
    LinkList L;
    InitList(&L);
    for (N_A = 0; c != '\n'; N_A++)
    {
        scanf("%d%d", &A[N_A].coefficient, &A[N_A].exponent);
        c = getchar();
    }
    for (N_B = 0; scanf("%d%d", &B[N_B].coefficient, &B[N_B].exponent) != EOF; N_B++)
        ;
    ListInsert(&L, 0, &result);
    for (int i = 0; i < N_A; i++)
        for (int j = 0; j < N_B; j++)
        {
            result.coefficient = A[i].coefficient * B[j].coefficient;
            result.exponent = A[i].exponent + B[j].exponent;
            Node *now = L.head;
            for (int k = 0; k < L.length; k++)
            {
                if (compar(&now->next->data, &result) == 0)
                {
                    ElemAdd(&now->next->data, &result);
                    break;
                }
                if (compar(&now->next->data, &result) < 0)
                {
                    Node *tmp = now->next;
                    now->next = (Node *)malloc(sizeof(Node));
                    now->next->data = result;
                    now->next->next = tmp;
                    L.length++;
                    break;
                }
                now = now->next;
            }
        }
    ListTraverse(&L, ElemPrint);

    return 0;
}
