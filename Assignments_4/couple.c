#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 205 // 200 + 5
typedef int Status;

typedef struct
{
    int type;
    int line_number;
} ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
    int type; // LOOK AT HERE!
} SqStack;

// 祖传屎山，从此开始->

Status InitStack(SqStack *S)
{
    S->top = -1;
    S->type = 0;
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

//<-祖传屎山，从此结束

int main()
{
    SqStack s;
    InitStack(&s);
    FILE *fp = fopen("example.c", "r");
    char str[MAXSIZE];

    char ans[MAXSIZE] = ""; // 按顺序出现的括号字符串

    int count = 0; // 行数
    while (fgets(str, MAXSIZE, fp) != NULL)
    {
        count++;
        char *last = "1", // 只要不是'/'应该都可以？
            *now = str;
        while (*now != '\n' && *now != '\0' && *now != '\r') // 一行结束时换行，文本结束时跳出循环
        {
            // 处理单双引号：直到找到反引号为止
            if (*now == '\"')
            {
                do
                {
                    now++;
                    if (*now == '\n' || *now == '\r')
                    // 再读一行
                    {
                        if (fgets(str, MAXSIZE, fp) == NULL)
                            return -1;
                        count++;
                        now = str;
                    }
                } while (*now != '\"');
            }
            else if (*now == '\'')
            {
                do
                {
                    now++;
                    if (*now == '\n' || *now == '\r')
                    // 再读一行
                    {
                        if (fgets(str, MAXSIZE, fp) == NULL)
                            return -1;
                        count++;
                        now = str;
                    }
                } while (*now != '\'');
            }
            // 处理"/*"注释：找到"*/"为止
            else if (*last == '/' && *now == '*')
            {
                { // 应对诸如"/*/xxxx)}*/"的情况
                    last = now;
                    now++;
                    if (*now == '\n' || *now == '\r')
                    {
                        if (fgets(str, MAXSIZE, fp) == NULL)
                            return -1;
                        count++;
                        now = str;
                    }
                }
                do
                {
                    last = now;
                    now++;
                    if (*now == '\n' || *now == '\r')
                    {
                        if (fgets(str, MAXSIZE, fp) == NULL)
                            return -1;
                        count++;
                        now = str;
                    }
                } while (*last != '*' || *now != '/');
            }
            // 处理"//"注释：直接换行
            else if (*last == '/' && *now == '/')
                break;

            else if (*now == '(') // 无条件入栈
            {
                ElemType e = {1, count};
                Push(&s, &e);
                s.type++;
                strcat(ans, "(");
            }
            else if (*now == ')')
            {
                ElemType e;
                if (StackEmpty(&s)) // 如果栈里没有左括号
                {
                    printf("without maching \')\' at line %d", count);
                    return 0;
                }
                Pop(&s, &e);
                if (e.type != 1) // 如果上一个左括号类型不同
                {
                    printf("without maching \')\' at line %d", count);
                    return 0;
                }
                else
                {
                    s.type--;
                    strcat(ans, ")");
                }
            }
            else if (*now == '{')
            {
                ElemType e;
                if (s.type) // 意为栈中是否还有'('
                {
                    do
                    {
                        Pop(&s, &e);
                    } while (e.type == 0); // 出栈直到取出最近的'('为止
                    printf("without maching \'(\' at line %d", e.line_number);
                    return 0;
                }
                else
                {
                    e.line_number = count;
                    e.type = 0;
                    Push(&s, &e);
                    strcat(ans, "{");
                }
            }
            else if (*now == '}')
            {
                ElemType e;
                if (StackEmpty(&s)) // 如果栈里没有左括号
                {
                    printf("without maching \'}\' at line %d", count);
                    return 0;
                }
                Pop(&s, &e);
                if (e.type != 0) // 如果上一个左括号类型不同
                {
                    printf("without maching \'}\' at line %d", count);
                    return 0;
                }
                else
                {
                    strcat(ans, "}");
                }
            }
            // 字符进位
            last = now;
            now++;
        }
    }
    if (StackEmpty(&s))
    {
        puts(ans);
        return 0;
    }
    else
    {
        // 不知道 最后还剩下的左括号 需不需要全部输出，不过 从前往后全部输出 和 只输出最后一个 都没过
        int i = s.top;
        printf("without maching \'%c\' at line %d\n", s.data[i].type ? '(' : '{', s.data[i].line_number);
        return 0;
    }
}
