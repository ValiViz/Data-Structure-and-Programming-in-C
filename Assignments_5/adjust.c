#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 10000

typedef int Status;
typedef struct Node
{
    int num;
    int passenger_volume;
    int loc;
} Node;

Status ScanNode(Node Tree[], Node *quick_search[])
{
    Node tmp;
    scanf("%d", &tmp.num);
    if (tmp.num == -1)
        return ERROR;
    int num, i = 1;
    scanf("%d", &num);
    while (num != -1)
    {
        if (quick_search[tmp.num])
        {
            Tree[3 * quick_search[tmp.num]->loc + i].num = num;
            quick_search[num] = &Tree[3 * quick_search[tmp.num]->loc + i];
            quick_search[num]->loc = 3 * quick_search[tmp.num]->loc + i;
        }
        else
        {
            return ERROR;
        }
        i++;
        scanf("%d", &num);
    }
    return OK;
}

Status ScanPassengerVolume(Node *quick_search[])
{
    int num, passenger_volume;
    if (scanf("%d%d", &num, &passenger_volume) != EOF)
    {
        quick_search[num]->passenger_volume = passenger_volume;
    }
    else
    {
        return ERROR;
    }
    return OK;
}

int compar(const void *a, const void *b)
{
    Node *A = *(Node **)a;
    Node *B = *(Node **)b;
    return B->passenger_volume == A->passenger_volume ? A->num - B->num : B->passenger_volume - A->passenger_volume;
}

Status SearchTree(Node Tree[], Node *boarding_gates[], int *length)
{
    *length = 0;
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (Tree[i].num == 0)
            continue;
        if (Tree[i].num < 100)
        {
            boarding_gates[*length] = &Tree[i];
            (*length)++;
        }
    }
    return OK;
}

Status AdjustPrint(Node *boarding_gates[], Node *adjusted_boarding_gates[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d->%d\n", adjusted_boarding_gates[i]->num, boarding_gates[i]->num);
    }
    return OK;
}

Status CopyNodeArray(Node *adjusted_boarding_gates[], Node *boarding_gates[], int length)
{
    for (int i = 0; i < length; i++)
    {
        adjusted_boarding_gates[i] = boarding_gates[i];
    }
    return OK;
}

int main()
{
    Node Tree[MAXSIZE] = {}, *quick_search[MAXSIZE], *boarding_gates[MAXSIZE], *adjusted_boarding_gates[MAXSIZE];
    Node tmp;
    scanf("%d", &tmp.num);
    Tree[0] = tmp;
    Tree[0].loc = 0;
    quick_search[tmp.num] = &Tree[0];
    if (tmp.num == -1)
        return ERROR;
    int num, i = 1;
    scanf("%d", &num);
    while (num != -1)
    {
        if (quick_search[tmp.num])
        {
            Tree[3 * quick_search[tmp.num]->loc + i].num = num;
            quick_search[num] = &Tree[3 * quick_search[tmp.num]->loc + i];
            quick_search[num]->loc = 3 * quick_search[tmp.num]->loc + i;
        }
        else
        {
            return ERROR;
        }
        i++;
        scanf("%d", &num);
    }
    while (ScanNode(Tree, quick_search))
        ;
    while (ScanPassengerVolume(quick_search))
        ;
    int length;
    SearchTree(Tree, boarding_gates, &length);
    CopyNodeArray(adjusted_boarding_gates, boarding_gates, length);
    qsort(adjusted_boarding_gates, length, sizeof(Node *), compar);
    AdjustPrint(boarding_gates, adjusted_boarding_gates, length);
    return 0;
}