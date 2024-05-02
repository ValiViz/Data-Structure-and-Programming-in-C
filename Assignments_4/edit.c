#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 32
typedef int Status;

typedef struct
{
    int option;
    int pos;
    char str[2048];
    int n;
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

char *strinsert(char *desk, const char *src)
{
    char tmp[2048];
    if (*desk != '\0')
        strcpy(tmp, desk);
    else
        *tmp = '\0';
    strcpy(desk, src);
    strcat(desk, tmp);
    return desk;
}

char *strdelete(char *desk, int n)
{
    
    char tmp[2048];
    if (strlen(desk) > n)
    {
        strcpy(tmp, desk + n);
        strcpy(desk, tmp);
        // strcpy(desk, desk + n);
    }
    else
        *desk = '\0';
    return desk;
}

int main()
{
    SqStack s, *S = &s;
    InitStack(S);

    char text[2048];
    int len;
    gets(text);
    int n;
    scanf("%d", &n);
    ElemType e;
    while (n--)
    {
        scanf("%d %d %s", &e.option, &e.pos, e.str);
        e.n = strlen(e.str);
        Push(S, &e);
    }

    while (scanf("%d", &e.option) != EOF)
    {
        switch (e.option)
        {
        case 1:
            scanf("%d %s", &e.pos, e.str);
            e.n = strlen(e.str);

            strinsert(text + e.pos, e.str);

            Push(S, &e);
            break;

        case 2:
            len = strlen(text);
            scanf("%d %d", &e.pos, &e.n);
            strcpy(e.str, text + e.pos);
            *(e.str + e.n) = '\0';

            strdelete(text + e.pos, e.n);

            e.n = (len - e.pos > e.n ? e.n : len - e.pos);
            Push(S, &e);
            break;

        case 3:
            if (StackEmpty(S))
                break;
            Pop(S, &e);
            switch (e.option)
            {
            case 1:
                strdelete(text + e.pos, e.n);
                break;

            case 2:
                strinsert(text + e.pos, e.str);
                break;
            }
            break;

        case -1:
            puts(text);
            return 0;
        }
    }
}