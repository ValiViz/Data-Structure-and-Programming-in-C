#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 /* 存储空间初始分配量 */

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/* 用于构造二叉树********************************** */
int treeIndex = 1;

/* ************************************************ */

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
    int num;
    int flag;
} RPNElem;

typedef struct
{
    RPNElem data[MAXSIZE];
    int length;
} RPN;

RPNElem Nil = {0, 0, 0}; /* 字符型以空格符为空 */

Status visit(ElemType e)
{
    printf("%c ", e);
    return OK;
}

Status InitStack(Stack *S)
{
    S->top = -1;
    return OK;
}

Status ClearStack(Stack *S)
{
    S->top = -1;
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
    S->data[++S->top] = *E;
    return OK;
}

Status Pop(Stack *S, ElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top--];
    return OK;
}

int StackLength(const Stack *S)
{
    return S->top + 1;
}

typedef struct BiTNode /* 结点结构 */
{
    RPNElem data;                   /* 结点数据 */
    struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode, *BiTree;

/* 构造空二叉树T */
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

/* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
void DestroyBiTree(BiTree *T)
{
    if (*T)
    {
        if ((*T)->lchild)                 /* 有左孩子 */
            DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
        if ((*T)->rchild)                 /* 有右孩子 */
            DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
        free(*T);                         /* 释放根结点 */
        *T = NULL;                        /* 空指针赋0 */
    }
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(BiTree T)
{
    if (T)
        return FALSE;
    else
        return TRUE;
}

#define ClearBiTree DestroyBiTree

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(BiTree T)
{
    int i, j;
    if (!T)
        return 0;
    if (T->lchild)
        i = BiTreeDepth(T->lchild);
    else
        i = 0;
    if (T->rchild)
        j = BiTreeDepth(T->rchild);
    else
        j = 0;
    return i > j ? i + 1 : j + 1;
}

/* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
RPNElem Root(BiTree T)
{
    if (BiTreeEmpty(T))
        return Nil;
    else
        return T->data;
}

/* 初始条件: 二叉树T存在，p指向T中某个结点 */
/* 操作结果: 返回p所指结点的值 */
RPNElem Value(BiTree p)
{
    return p->data;
}

/* 给p所指结点赋值为value */
void Assign(BiTree p, RPNElem value)
{
    p->data = value;
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
int PreOrderTraverse(BiTree T)
{
    if (T->data.flag == 1)
        return T->data.num;
    switch (T->data.sign)
    {
    case '+':
        return PreOrderTraverse(T->lchild) + PreOrderTraverse(T->rchild);
    case '-':
        return PreOrderTraverse(T->lchild) - PreOrderTraverse(T->rchild);
    case '*':
        return PreOrderTraverse(T->lchild) * PreOrderTraverse(T->rchild);
    case '/':
        return PreOrderTraverse(T->lchild) / PreOrderTraverse(T->rchild);
    default:
        break;
    }
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    InOrderTraverse(T->lchild); /* 中序遍历左子树 */
    printf("%c", T->data);      /* 显示结点数据，可以更改为其它对结点操作 */
    InOrderTraverse(T->rchild); /* 最后中序遍历右子树 */
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    PostOrderTraverse(T->lchild); /* 先后序遍历左子树  */
    PostOrderTraverse(T->rchild); /* 再后序遍历右子树  */
    printf("%c", T->data);        /* 显示结点数据，可以更改为其它对结点操作 */
}

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

Status IsNum(const char *p)
{
    return *p >= '0' && *p <= '9';
}

Status InitRPN(RPN *C)
{
    C->length = 0;
    return OK;
}

Status EnRPN(RPN *C, void *E, int flag)
{
    if (C->length >= MAXSIZE)
        return ERROR;
    if (flag == 1)
    {
        C->data[C->length].num = *(int *)E;
    }
    else if (flag == 2)
    {
        C->data[C->length].sign = *(char *)E;
    }
    C->data[C->length].flag = flag;
    C->length++;
    return OK;
}

Status DataCopy(RPNElem *desk, RPNElem *src)
{
    src->flag = desk->flag;
    src->num = desk->num;
    src->sign = desk->sign;
    return OK;
}

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
        int num;
        if (IsNum(p))
        {
            sscanf(p, "%d", &num);
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

    BiTree TreeStack[1000];
    int top = 0;
    for(int i = 0; i < C->length; i++)
    {
        if(C->data[i].flag == 1)
        {
            TreeStack[top] = (BiTNode *)malloc(sizeof(BiTNode));
            DataCopy(&C->data[i], &TreeStack[top]->data);
            top++;
        }
        else if(C->data[i].flag == 2)
        {
            BiTree tmp = (BiTNode *)malloc(sizeof(BiTNode));
            DataCopy(&C->data[i], &tmp->data);
            tmp->lchild = TreeStack[top - 2];
            tmp->rchild = TreeStack[top - 1];
            TreeStack[top - 2] = tmp;
            top--;
        }
    }
    BiTree Result = TreeStack[0];
    if(Result->data.flag == 1)
        printf("%d ", Result->data.num);
    else
        printf("%c ", Result->data.sign);
    if(Result->lchild->data.flag == 1)
        printf("%d ", Result->lchild->data.num);
    else
        printf("%c ", Result->lchild->data.sign);
    if(Result->rchild->data.flag == 1)
        printf("%d\n", Result->rchild->data.num);
    else
        printf("%c\n", Result->rchild->data.sign);

    int answer = PreOrderTraverse(Result);
    printf("%d\n", answer);
    return 0;
}