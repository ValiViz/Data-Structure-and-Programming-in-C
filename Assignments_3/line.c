/*
连续线段
【问题描述】
平面上两个点（一个点由(x,y)坐标组成）可构成一个线段，两个线段如果有一个端点相同，则可构成一个连续线段。假设构成线段的两个端点为v1(x1,y1)和v2(x2,y2)，在此满足x1<x2，其中v1称为线段的起点，v2为线段的终点。同样，对于连续线段来说，在此满足xi<xi+1（i=1...n-1，n为连续线段中的端点数，xi为相应端点的X轴坐标）。输入一组线段（用两个端点的x、y坐标表示线段，线段个数大于等于2，小于等于100），编程计算出连续线段中包含最多线段数的线段，输出相应的线段数和起点位置（注意，不是最长的连续线段，是包含最多线段的连续线段）。例如：

1.jpg

上图中有10个线段，其中5、10、4号线段连成了一条连续线段，线段数3条，起点位置为5号线段的左端点；6、8、2、3、9号线段连成了另一条连续线段，该连续线段包含的线段数最多，为5条，起点位置是6号线段的左端点。
注意：
1）不考虑线段中间相交的情况；
2）不会有三条或三条以上的线段共一个端点；
3）只会出现一条包含最多线段的连续线段；

【输入形式】
先从控制台输入线段数，然后从下一行开始分行输入各线段两个端点的x、y坐标，其中第一个端点的X轴坐标小于第二个端点的X轴坐标，即x1<x2，x、y坐标都用整数表示，不会超过int的表示范围。各整数坐标值间以一个空格分隔。
【输出形式】
先在控制台输出包含最多线段数的连续线段的线段数，然后输出连续线段的起点的x、y坐标，输出数据都以一个空格分隔。
【样例输入】

10

80 75 125 75

60 40 80 55

80 55 90 20

140 120 195 205

10 111 70 165

22 35 43 43

22 175 80 205

43 43 60 40

90 20 125 60

70 165 140 120

【样例输出】
5 22 35
【样例说明】
输入了十个线段，第一个线段两个端点分别为(80,75）和(125,75），其它线段类似，如上图所示，这些线段所构成的连续线段中包含最多线段数的连续线段的线段数为5，起点为(22,35），所以输出：5 22 35。
【评分标准】
通过所有测试点将得满分。提交程序名为line.c。
*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;

typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
    int count;
} ElemType;

// int compar(const void *Ea, const void *Eb)
// {
//     ElemType ea = *(ElemType *)Ea, eb = *(ElemType *)Eb;
//     （注意替换）
// }

// Status visit(ElemType *E)
// {
//     （注意替换）
//     return OK;
// }

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status ListEmpty(const SqList *L)
{
    if (L->length == 0)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status GetElem(const SqList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    *E = L->data[i];
    return OK;
}

int LocateElem(const SqList *L, const ElemType *E, int (*compar)(const void *, const void *))
{
    for (int i = 0; i < L->length; i++)
    {
        if (compar(&L->data[i], E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(SqList *L, int i, const ElemType *E)
{

    if (i > L->length || i < 0 || L->length >= MAXSIZE)
        return ERROR;
    for (int j = L->length; j > i; j--)
        L->data[j] = L->data[j - 1];
    L->data[i] = *E;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0 || L->length <= 0)
        return ERROR;
    *E = L->data[i];
    L->length--;
    for (; i < L->length; i++)
    {
        L->data[i] = L->data[i + 1];
    }
    return OK;
}

int ListLength(const SqList *L)
{
    return L->length;
}

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    for (int i = 0; i < L->length; i++)
        if (!func_visit(&L->data[i]))
            return ERROR;
    return OK;
}

// Status unionL(SqList *desk, const SqList *src)
// {
//     ElemType e;
//     for (int i = 0; i < src->length; i++)
//     {
//         GetElem(src, i, &e);
//         if (!LocateElem(desk, &e, compar))
//             if (!ListInsert(desk, desk->length, &e))
//                 return ERROR;
//         return OK;
//     }
// }

Status CanBeConnected(const ElemType *A, const ElemType *B)
{
    return A->x2 == B->x1 && A->y2 == B->y1;
}

Status Connect(ElemType *A, ElemType *B)
{
    A->x2 = B->x2;
    A->y2 = B->y2;
    A->count += B->count;
    return OK;
}

Status DulConnect(ElemType *A, ElemType *B)
{
    A->x1 = B->x1;
    A->y1 = B->y1;
    A->count += B->count;
    return OK;
}

int main()
{
    SqList Line;
    ElemType a;
    scanf("%d", &Line.length);
    for (int i = 0; i < Line.length; i++)
    {
        scanf("%d%d%d%d", &Line.data[i].x1, &Line.data[i].y1, &Line.data[i].x2, &Line.data[i].y2);
        Line.data[i].count = 1;
    }

    for (int i = 0; i < Line.length; i++)
    {
        for (int j = 0; j < Line.length; j++)
        {
            if (CanBeConnected(&Line.data[i], &Line.data[j]))
            {
                Connect(&Line.data[i], &Line.data[j]);
                ListDelete(&Line, j, &a);
                if (i > j)
                    i--;
                j--;
            }
            else if (CanBeConnected(&Line.data[j], &Line.data[i]))
            {
                DulConnect(&Line.data[i], &Line.data[j]);
                ListDelete(&Line, j, &a);
                if (i > j)
                    i--;
                j--;
            }
        }
    }

    int flag = 0;
    for (int i = 0; i < Line.length; i++)
    {
        flag = Line.data[i].count > Line.data[flag].count ? i : flag;
    }

    printf("%d %d %d\n", Line.data[flag].count, Line.data[flag].x1, Line.data[flag].y1);

    return 0;
}