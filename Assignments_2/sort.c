#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[20];
    char phone[20];
} PERSON;

int cmp(const void *a, const void *b)
{
    PERSON pa = *(PERSON*)a, pb = *(PERSON*)b;
    return strcmp(pa.name, pb.name);
}

int main()
{
    int count = 0;
    int N;
    scanf("%d", &N);
    PERSON list[105];
    PERSON now;
    while(N--)
    {
        scanf("%s%s", now.name, now.phone);
        int again = 0;
        for(int i = 0; i < count; i++)
        {
            if(strcmp(now.phone, list[i].phone) == 0)
            {
                goto QUIT;
            }
            if(strcmp(now.name, list[i].name) == 0)
            {
                if(!again)
                {
                    strcat(now.name, "_1");
                }
                else
                {
                    now.name[strlen(now.name) - 1] = '1' + again;
                }
                again++;
                continue;
            }
        }
        strcpy(list[count].name, now.name);
        strcpy(list[count].phone, now.phone);
        count++;
        QUIT:
        ;
    }

    qsort(list, count, sizeof(PERSON), cmp);

    for(int i = 0; i < count; i++)
    {
        printf("%s %s\n", list[i].name, list[i].phone);
    }

    return 0;
}