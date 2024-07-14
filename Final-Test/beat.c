#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 200
typedef int Status;

typedef struct Node
{
    int num;
    int type;
    Status work_status;
    int child_size;
    struct Node *child[32];
    int parent_num;
    struct Node *parent;
} Node;
int cmp(const void *a, const void *b)
{
    Node * A = *(Node **)a, *B = *(Node **)b;
    return A->num - B->num;
}
Status InitNode(Node *N)
{
    N->num = N->type = N->child_size = N->parent_num = N->work_status = 0;
    N->parent = NULL;
    return OK;
}

Node *Search(int num, Node *N)
{
    Node *ans = NULL;
    if (num == N->num)
        return N;
    for (int i = 0; i < N->child_size; i++)
    {
        ans = Search(num, N->child[i]);
        if (ans != NULL)
            return ans;
    }
    return NULL;
}

Status set_child_OK(Node *N)
{
    for (int i = 0; i < N->child_size; i++)
    {
        N->child[i]->work_status = OK;
        set_child_OK(N->child[i]);
    }
    return OK;
}
Status NodePrint(Node *N)
{
    
    if(N->type == 1)
    {
        if(N->work_status == OK)
        return OK;
        printf("%d ", N->num);
    }
    if(N->type == 0)
    {
        Node *TMP[32];
        for(int i = 0; i < N->child_size; i++)
        TMP[i] = N->child[i];
        qsort(TMP, N->child_size, sizeof(Node *), cmp);
        if(N->work_status != OK)
        printf("%d ", N->num);
        for(int i = 0; i < N->child_size; i++)
        {
            NodePrint(TMP[i]);
        }
        return OK;
    }

}
int main()
{
    int N;
    scanf("%d", &N);
    Node tmp[N], *Root = &tmp[0];
    int nosense;

    for (int i = 0; i < N; i++)
    {
        InitNode(&tmp[i]);
        scanf("%d%d%d%d", &tmp[i].num, &tmp[i].parent_num, &nosense, &tmp[i].type);
        if (tmp[i].parent_num != -1)
        {
            Node *P = Search(tmp[i].parent_num, Root);
            if (P)
            {
                P->child[P->child_size++] = &tmp[i];
                tmp[i].parent = P;
            }
        }
    }
    int beat_num;
    scanf("%d", &beat_num);
    while (beat_num != -1)
    {
        Node *N = Search(beat_num, Root);
        N->work_status = OK;
        while (N != Root)
        {
            N = N->parent;
            N->work_status = OK;
        }

        scanf("%d", &beat_num);
    }
    for (int i = 0; i < N; i++)
    {
        if (tmp[i].type == 1)
        {
            if (tmp[i].work_status != OK)
            {
                Node *Bug = &tmp[i];
                while (Bug->parent->work_status != OK)
                {
                    Bug = Bug->parent;
                }
                Bug->work_status = 2;
                set_child_OK(Bug);
            }
        }
    }
    NodePrint(Root);
}