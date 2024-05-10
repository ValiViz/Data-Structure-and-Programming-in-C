/*
多项式相乘
【问题描述】（建议用链表实现）

编写一个程序实现两个一元多项式相乘。

【输入形式】

首先输入第一个多项式中系数不为0的项的系数和指数，以一个空格分隔。且该多项式中各项的指数均为0或正整数，系数和最高幂次不会超过int类型的表示范围。对于多项式 anxn +a n-1 x n-1 +......+ a1x1 + a0x0 的输入方法如下：
an  n  a n-1  n-1 ......  a1  1  a0  0 
即相邻两个整数分别表示表达式中一项的系数和指数。在输入中只出现系数不为0的项。最后一项的指数后没有空格，只有一个回车换行符。
按照上述方式再输入第二个多项式。

【输出形式】

将运算结果输出到屏幕。将系数不为0的项按指数从高到低的顺序输出，每次输出其系数和指数，均以一个空格分隔，最后一项的指数后也可以有一个空格。

【样例输入】

10 80000 2 6000 7 300 5 10 18 0
3 6000 5 20 8 10 6 0

【样例输出】

30 86000 50 80020 80 80010 60 80000 6 12000 21 6300 10 6020 31 6010 66 6000 35 320 56 310 42 300 25 30 130 20 174 10 108 0

【样例说明】

输入的两行分别代表如下表达式：
10x80000 + 2x6000 + 7x300 + 5x10 + 18
3x6000 + 5x20 + 8x10 + 6
相乘结果为：
30x86000 + 50x80020 + 80x80010 + 60x80000 + 6x12000 + 21x6300 + 10x6020 + 31x6010 + 66x6000 + 35x320 + 56x310 + 42x300 + 25x30 + 130x20 + 174x10 + 108

提示：利用链表存储多项式的系数和指数。

【评分标准】

该题要求输出相乘后多项式中系数不为0的系数和指数，共有5个测试点。上传C语言文件名为multi.c。
*/

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
