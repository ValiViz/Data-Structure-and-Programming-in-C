// 24 1 5 3 / + 36 6 / 2 / + 2 - / 12 2 / 2 / *
// 24/(1+5/3+36/6/2-2)*12/2/2

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;
typedef char ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
    int flag;
} Stack;

typedef struct
{
    char sign;
    double num;
    int flag;
} RPNElem;

typedef struct
{
    RPNElem data[MAXSIZE];
    int length;
} RPN;

int max(int a, int b)
{
    return a > b ? a : b;
}

int SignFlag(char *p)
{
    if (*p == ')')
        return 0;
    if (*p == '+' || *p == '-')
        return 1;
    if (*p == '*' || *p == '/')
        return 2;
    if (*p == '(')
        return 3;
    // if (*p == ')')
    //     return 4;
}

Status InitStack(Stack *S)
{
    S->top = -1;
    S->flag = 0;
    return OK;
}

Status StackEmpty(const Stack *S)
{
    if (S->top >= 0)
        return FALSE;
    return TRUE;
}

Status GetTop(const Stack *S, ElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top];
    return OK;
}

Status Push(Stack *S, const ElemType *E)
{
    if (S->top >= MAXSIZE - 1)
        return ERROR;
    S->data[S->top + 1] = *E;
    S->top++;
    return OK;
}

Status Pop(Stack *S, ElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top--];
    return OK;
}

Status IsNum(const char *p)
{
    return *p >= '0' && *p <= '9';
}

Status InitRPN(RPN *C)
{
    C->length = 0;
    return OK;
}

Status WorkRPN(RPN *C)
{
    switch (C->data[C->length - 1].sign)
    {
    case '+':
        C->data[C->length - 3].num += C->data[C->length - 2].num;
        break;
    case '-':
        C->data[C->length - 3].num -= C->data[C->length - 2].num;
        break;
    case '*':
        C->data[C->length - 3].num *= C->data[C->length - 2].num;
        break;
    case '/':
        C->data[C->length - 3].num /= C->data[C->length - 2].num;
        break;
    }
    C->length -= 2;
}

Status EnRPN(RPN *C, void *E, int flag)
{
    if (C->length >= MAXSIZE)
        return ERROR;
    if (flag == 1)
    {
        C->data[C->length].num = *(double *)E;
    }
    else if (flag == 2)
    {
        C->data[C->length].sign = *(char *)E;
    }
    C->data[C->length].flag = flag;
    C->length++;
    if (flag == 2)
        WorkRPN(C);
    return OK;
}
//((6/2+3) *(55-3)-(5 *(55+2)) /2 )=
//((1+1)+1)=
int main()
{
    Stack stack, *S = &stack;
    InitStack(S);
    RPN cal, *C = &cal;
    InitRPN(C);
    int n = 0;

    char str[MAXSIZE], *p = str;
    gets(str);

    while (*p != '=')
    {
        double num;
        if (IsNum(p))
        {
            sscanf(p, "%lf", &num);
            EnRPN(C, &num, 1);
            do
            {
                p++;
            } while (IsNum(p));
        }
        else if(*p != ' ')
        {
            if (SignFlag(p) > S->flag)
            {
                Push(S, p);
                if (SignFlag(p) != 3)
                    S->flag = SignFlag(p);
                else
                    S->flag = 0;
            }
            else if (SignFlag(p) < 3 && SignFlag(p) > 0)
            {
                ElemType tmp;
                do
                {
                    Pop(S, &tmp);
                    EnRPN(C, &tmp, 2);
                    if(S->data[S->top] != '(')
                        S->flag = StackEmpty(S) ? 0 : SignFlag(&S->data[S->top]);
                    else
                        S->flag = 0;
                } while (SignFlag(p) <= S->flag);
                Push(S, p);
                S->flag = SignFlag(p);
            }
            else
            {
                ElemType tmp = '+';
                Pop(S, &tmp);
                while (SignFlag(&tmp) != 3)
                {
                    EnRPN(C, &tmp, 2);
                    Pop(S, &tmp);
                }
                if(S->data[S->top] != '(')
                        S->flag = StackEmpty(S) ? 0 : SignFlag(&S->data[S->top]);
                    else
                        S->flag = 0;
            }
            p++;
        }
        else
        {
            p++;
        }
    }
    while(!StackEmpty(S))
    {
        ElemType tmp;
        Pop(S, &tmp);
        EnRPN(C, &tmp, 2);
    }

    printf("%.2lf\n", C->data[0].num);
    return 0;
}