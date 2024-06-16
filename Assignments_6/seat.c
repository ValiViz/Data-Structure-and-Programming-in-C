#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000
#define min(a, b) a > b ? b : a
typedef int Status;
typedef struct
{
    int ID;
    char name[21];
    int seat_number;
} STUDENT;
int compare_seat_number_and_ID(const void *a, const void *b)
{
    STUDENT *A = (STUDENT *)a, *B = (STUDENT *)b;
    return A->seat_number == B->seat_number ? A->ID - B->ID : A->seat_number - B->seat_number;
}
int compare_ID(const void *a, const void *b)
{
    STUDENT *A = (STUDENT *)a, *B = (STUDENT *)b;
    return A->ID - B->ID;
}
Status scan_student(int n, FILE *fp, STUDENT *T)
{
    STUDENT tmp;
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d%s%d", &tmp.ID, tmp.name, &tmp.seat_number);
        T[i] = tmp;
    }
    fclose(fp);
    return OK;
}
Status print_table(int n, FILE *fp, STUDENT *T)
{
    for(int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %d\n", T[i].ID, T[i].name, T[i].seat_number);
    }
    fclose(fp);
    return OK;
}

int main()
{
    int N;
    scanf("%d", &N);
    STUDENT table[N];
    FILE *IN = fopen("in.txt", "r");
    FILE *OUT = fopen("out.txt", "w");
    scan_student(N, IN, table);
    qsort(table, N, sizeof(STUDENT), compare_seat_number_and_ID);
    int Q = min(table[N - 1].seat_number, N);
    int cur = 0;
    int poi = N;
    for (int i = 1; i <= Q; i++)
    {
        while (cur < N && table[cur].seat_number < i)
            cur++;
        if (cur < N && table[cur].seat_number == i)
        {
            cur++;
            continue;
        }
        else if (cur >= N)
        {
            break;
        }
        else
        {
            table[--poi].seat_number = i;
        }
    }
    qsort(table, N, sizeof(STUDENT), compare_seat_number_and_ID);
    int M = table[N - 1].seat_number;
    int last = 0;
    for(int i = 0; i < N;i ++)
    {
        if(table[i].seat_number == last)
        {
            table[i].seat_number = ++M;
        }
        else
        {
            last = table[i].seat_number;
        }
    }
    qsort(table, N, sizeof(STUDENT), compare_ID);
    print_table(N, OUT, table);
}