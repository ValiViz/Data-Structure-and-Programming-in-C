#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[31];
    int size;
} FUNC;
typedef struct
{
    FUNC stack[100];
    int top;
    int size;
} STACK;
void init_stack(STACK *S)
{
    S->top = 0;
    S->size = 0;
    return;
}
int main()
{
    int n;
    scanf("%d", &n);
    STACK s, m1, m2;
    init_stack(&s);
    init_stack(&m1);
    init_stack(&m2);
    FUNC func[100];
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", func[i].name, &func[i].size);
    }
    char op[10];
    while (scanf("%s", op) != EOF)
    {
        char func_name[31];
        int x;
        switch (*op)
        {
        case 'c':
            scanf("%s", func_name);
            int i;
            for (i = 0; i < n; i++)
            {
                if (strcmp(func_name, func[i].name) == 0)
                    break;
            }
            s.stack[s.top++] = func[i];
            s.size += s.stack[s.top - 1].size;
            break;
        case 'r':
            s.size -= s.stack[(s.top--) - 1].size;
            if (s.top == 0)
                goto END;
            break;
        case 'f':
            scanf("%d", &x);
            while (s.top > x + 1)
            {
                s.size -= s.stack[(s.top--) - 1].size;
            }
            break;
        default:
            break;
        }
        if (s.top > m1.top)
            m1 = s;
        if (s.size > m2.size)
            m2 = s;
    }
END:
    printf("%d\n", m1.top);
    for (int i = 0; i < m1.top; i++)
    {
        printf("%s(%d) ", m1.stack[i].name, m1.stack[i].size);
    }
    printf("\n");
    printf("%d\n", m2.size);
    for (int i = 0; i < m2.top; i++)
    {
        printf("%s(%d) ", m2.stack[i].name, m2.stack[i].size);
    }
    printf("\n");
}
