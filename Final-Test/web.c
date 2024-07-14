#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 200
typedef int Status;

typedef struct
{
    char name[MAXSIZE];
    int count;
} ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
} SqStack;

Status InitStack(SqStack *S)
{
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

char *getname(char *desk, char *src)
{
    char *p = src, *q = desk;
    p += 8;
    while (*p != '/')
    {
        *q = *p;
        p++;
        q++;
    }
    return desk;
}

Status add(ElemType count[], int *N, ElemType now)
{
    int n = *N;
    char name[MAXSIZE];
    getname(name, now.name);
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(name, count[i].name) == 0)
        {
            break;
        }
    }
    if (i == n)
    {
        strcpy(count[n].name, name);
        count[n].count = 1;
        (*N)++;
    }
    else
    {
        count[i].count++;
    }
    return OK;
}
Status ElemPrint(ElemType *E)
{
    printf("%s\n", E->name);
    return OK;
}
int main()
{
    SqStack forward, back;
    InitStack(&forward);
    InitStack(&back);
    ElemType count[MAXSIZE], now = {"https://www.baidu.com/", 0};
    int n = 0;
    add(count, &n, now);
    ElemPrint(&now);
    int config = 0;
    char op[10];
    while (scanf("%s", op) != EOF)
    {
        switch (*op)
        {
        case 'V':
            Push(&back, &now);
            scanf("%s", now.name);
            ClearStack(&forward);
            add(count, &n, now);
            ElemPrint(&now);
            break;
        case '<':
            if (!StackEmpty(&back))
            {
                Push(&forward, &now);
                Pop(&back, &now);
                add(count, &n, now);
                ElemPrint(&now);
            }
            break;
        case '-':
            if (!StackEmpty(&forward))
            {
                Push(&back, &now);
                Pop(&forward, &now);
                add(count, &n, now);
                ElemPrint(&now);
            }
            break;
        case 'Q':
            goto END;
        default:
            break;
        }
    }
END:
    scanf("%d", &config);
    if (config == 1)
    {
        int max = 0;
        int poi = 0;
        for (int i = 0; i < n; i++)
        {
            if (count[i].count > max)
            {
                poi = i;
                max = count[i].count;
            }
        }
        printf("%s %d\n", count[poi].name, count[poi].count);
    }

    return 0;
}