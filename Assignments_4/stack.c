#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
typedef int Status;

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
} SqStack;

Status InitStack(SqStack *S)
{
    // S = (SqStack *)malloc(sizeof(SqStack));
    S->top = -1;
    return OK;
}

Status ClearStack(SqStack *S)
{
    S->top = -1;
    return OK;
}

Status StackEmpty(const SqStack *S)
{
    if (S->top >= 0)
        return FALSE;
    return TRUE;
}

Status GetTop(const SqStack *S, ElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top];
    return OK;
}

Status Push(SqStack *S, const ElemType *E)
{
    if (S->top >= MAXSIZE - 1)
        return ERROR;
    S->data[++S->top] = *E;
    return OK;
}

Status Pop(SqStack *S, ElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top--];
    return OK;
}

int StackLength(const SqStack *S)
{
    return S->top + 1;
}

int main()
{
    int option;
    SqStack S;
    SqStack *Stack = &S;
    InitStack(Stack);
    ElemType e;
    while (TRUE)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            scanf("%d", &e);
            if (!Push(Stack, &e))
                printf("error ");
            break;
        case 0:
            if (!Pop(Stack, &e))
                printf("error ");
            else
                printf("%d ", e);
            break;
        case -1:
            return 0;
        }
    }

    return -1;
}