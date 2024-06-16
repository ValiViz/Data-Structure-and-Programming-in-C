#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000
#define min(a, b) a > b ? b : a
typedef int Status;
int num[100];
void adjust(int k[], int i, int n, int *count)
{
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n)
    {
        if (j < n - 1 && k[j] < k[j + 1])
            j++;
        (*count)++;
        if (temp >= k[j])
            break;
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
}
void merge(int x[], int tmp[], int left, int leftend, int rightend, int *count)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {
        (*count)++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}
void mSort(int k[], int tmp[], int left, int right, int *count)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        mSort(k, tmp, left, center, count);
        mSort(k, tmp, center + 1, right, count);
        merge(k, tmp, left, center, right, count);
    }
}
void mergeSort(int k[], int n, int *count)
{
    int *tmp;
    tmp = (int *)malloc(sizeof(int) * n);
    if (tmp != NULL)
    {
        mSort(k, tmp, 0, n - 1, count);
        free(tmp);
    }
    else
        printf("No space for tmp array!!!\n");
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void quickSort(int k[], int left, int right, int *count)
{
    int i, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            (*count)++;
            if (k[i] < k[left])
                swap(&k[++last], &k[i]);
        }
        swap(&k[left], &k[last]);
        quickSort(k, left, last - 1, count);
        quickSort(k, last + 1, right, count);
    }
}
int main()
{
    int n, op;
    scanf("%d%d", &n, &op);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    int count = 0;
    switch (op)
    {
    case 1:
        for (int i = 0; i < n - 1; i++)
        {
            int cur = i;
            for (int j = i + 1; j < n; j++)
            {
                count++;
                if (num[j] < num[cur])
                {
                    cur = j;
                }
            }
            if (cur != i)
            {
                int tmp = num[i];
                num[i] = num[cur];
                num[cur] = tmp;
            }
        }
        break;
    case 2:
    {
        int flag = 1;
        int temp;
        for (int i = n - 1; i > 0 && flag == 1; i--)
        {
            flag = 0; /* 每趟排序前标志flag置0 */
            for (int j = 0; j < i; j++)
            {
                count++;
                if (num[j] > num[j + 1])
                {
                    temp = num[j];
                    num[j] = num[j + 1];
                    num[j + 1] = temp; /* 交换两个元素的位置*/
                    flag = 1;          /* 标志flag置1 */
                }
            }
        }
    }
    break;
    case 3:
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            adjust(num, i, n, &count);
        }
        for (int i = n - 1; i >= 1; i--)
        {
            int tmp = num[0];
            num[0] = num[i];
            num[i] = tmp;
            adjust(num, 0, i, &count);
        }
        break;
    case 4:
        mergeSort(num, n, &count);
        break;
    case 5:
        quickSort(num, 0, n - 1, &count);
        break;
    default:
        break;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\n%d", count);
    return 0;
}