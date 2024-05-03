#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000
#define MAX_TREE_SIZE 1000

typedef int Status;
typedef struct
{
    int data;
} ElemType;
typedef ElemType SqBiTree[MAX_TREE_SIZE];

typedef struct
{
    int level;
    int order;
} Position;

const ElemType Nil = {0};

int compar(const void *E1, const void *E2)
{
    ElemType e1 = *(ElemType *)E1, e2 = *(ElemType *)E2;
    return e1.data - e2.data;
}

Status InitBiTree(SqBiTree T)
{
    for (int i = 0; i < MAX_TREE_SIZE; i++)
    {
        T[i] = Nil;
    }
    return OK;
}

Status CreateBiTree(SqBiTree T, ElemType E[], int length)
{
    if (length > MAX_TREE_SIZE)
        return ERROR;
    for (int i = 0; i < length; i++)
    {
        T[i] = E[i];
        if (i != 0 && compar(&T[(i - 1) / 2], &Nil) == 0 && T[i] != Nil)
            return ERROR;
    }
    return OK;
}

Status BiTreeEmpty(SqBiTree T)
{
    return compar(&T[0], &Nil) == 0;
}

int BiTreeDepth(SqBiTree T)
{
    
}