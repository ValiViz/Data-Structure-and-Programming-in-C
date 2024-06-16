#include <stdio.h>
#include <stdlib.h>
typedef int Status;
typedef struct Student
{
    int number;
    char name[16];
    int computer_number;
    Status is_errored;
} Student;
Status init_student(Student *S)
{
    S->number = 0;
    *(S->name) = '\0';
    S->computer_number = 0;
    S->is_errored = 0;
    return 1;
}
int compar(const void *A, const void *B)
{
    Student *SA = (Student *)A, *SB = (Student *)B;
    return SA->number - SB->number;
}
Student list[200];
Student error_list[200];
int main()
{
    int N;
    int top = 0;
    scanf("%d", &N);
    int time = 0;
    for (int i = 0; i < N; i++)
    {
        init_student(&list[i]);
        scanf("%d%s%d%d", &list[i].number, &list[i].name, &list[i].computer_number, &time);
    }
    for (int i = 0; i < N; i++)
    {
        if (list[i].is_errored == 1)
            continue;
        for (int j = i + 1; j < N; j++)
        {
            if (list[i].number == list[j].number)
            {
                if (list[i].computer_number != list[j].computer_number)
                {
                    if (list[i].is_errored == 0)
                    {
                        error_list[top] = list[i];
                        top++;
                    }
                    list[i].is_errored = list[j].is_errored = 1;
                }
                else
                    list[j].is_errored = 1;
            }
        }
    }
    qsort(error_list, top, sizeof(Student), compar);
    for (int i = 0; i < top; i++)
    {
        printf("%d %s\n", error_list[i].number, error_list[i].name);
    }
    return 0;
}