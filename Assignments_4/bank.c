#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 1000
typedef int Status;

enum CustomerCategories
{
    SIMPLE_SERVICE = 1,
    ORDINARY_SERVICE,
    COMPLEX_SERVICE
};

enum ServiceCategories
{
    PERSONAL = 0,
    OTHER
};

typedef struct
{
    int number;
    enum CustomerCategories category;
    int enqueued_cycles_count;
    int dequeued_cycles_count;
} Customer;

typedef struct
{
    Status is_switchable;
    enum ServiceCategories category;
    Status left_occupied_cycles_count;
} Window;

typedef struct
{
    Customer line[MAXSIZE];
    int front;
    int rear;
} SqQueue;

Status InitQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

Status QueueEmpty(const SqQueue *Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    return FALSE;
}

int QueueLength(const SqQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

Status GetHead(const SqQueue *Q, Customer *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    *E = Q->line[Q->front];
    return OK;
}

Status EnQueue(SqQueue *Q, const Customer *E)
{
    if ((Q->rear + MAXSIZE + 1) % MAXSIZE == Q->front)
        return ERROR;
    Q->line[Q->rear] = *E;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, Customer *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    *E = Q->line[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}
int customers_average_wait_length(int length, Window service_windows[])
{
    int windows_number = 5;
    int personal_windows_number = 0;
    for (int i = 0; i < windows_number; i++)
    {
        if (service_windows[i].category == PERSONAL)
        {
            personal_windows_number++;
        }
    }
    return length / personal_windows_number;
}
Status Input(int *, int *, SqQueue *);
Status CustomersArrive(int, SqQueue *, SqQueue *);
Status WindowsIncrease(SqQueue *, Window *);
Status OfferService(int, SqQueue *, Window *);
Status WindowsDecrease(SqQueue *, Window *);
Status WindowSwitch(Window *, enum ServiceCategories);
Status Output(Customer *);
Status Test(SqQueue *);

int main()
{
    Window service_windows[5] = {{FALSE, PERSONAL, 0}, {FALSE, PERSONAL, 0}, {FALSE, PERSONAL, 0}, {TRUE, OTHER, 0}, {TRUE, OTHER, 0}};
    int T, customers_number[MAXSIZE];
    SqQueue to_arrive_queue, *aQ = &to_arrive_queue, wait_queue, *wQ = &wait_queue;
    InitQueue(aQ);
    InitQueue(wQ);

    Input(&T, customers_number, aQ);

    int cycles_count = 1;
    while (!(QueueEmpty(aQ) && QueueEmpty(wQ)))
    {
        if (CustomersArrive(cycles_count, aQ, wQ))
            WindowsIncrease(wQ, service_windows);
        OfferService(cycles_count, wQ, service_windows);
        WindowsDecrease(wQ, service_windows);
        cycles_count++;
    }
    return 0;
}

Status Input(int *T, int customers_number[], SqQueue *aQ)
{
    scanf("%d", T);
    for (int cycles_count = 1; cycles_count <= *T; cycles_count++)
    {
        scanf("%d", &customers_number[cycles_count]);
    }
    Customer tmp;
    int number = 1;
    for (int cycles_count = 1; cycles_count <= *T; cycles_count++)
    {
        tmp.enqueued_cycles_count = cycles_count;
        for (int count = 0; count < customers_number[cycles_count]; count++)
        {
            scanf("%d", &tmp.category);
            tmp.number = number++;
            EnQueue(aQ, &tmp);
        }
    }
}

Status CustomersArrive(int cycles_count, SqQueue *aQ, SqQueue *wQ)
{
    if (QueueEmpty(aQ))
        return ERROR;
    Customer tmp;
    GetHead(aQ, &tmp);
    while (tmp.enqueued_cycles_count <= cycles_count)
    {
        DeQueue(aQ, &tmp);
        EnQueue(wQ, &tmp);
        if (QueueEmpty(aQ))
            return OK;
        GetHead(aQ, &tmp);
    }
    // Test(aQ);
    // Test(wQ);
    return OK;
}

Status WindowsIncrease(SqQueue *wQ, Window service_windows[])
{
    int length = QueueLength(wQ);
    while (customers_average_wait_length(length, service_windows) >= 7)
    {
        if (!WindowSwitch(service_windows, PERSONAL))
        {
            return OK;
        }
    }
    return OK;
}
Status OfferService(int cycles_count, SqQueue *wQ, Window *service_windows)
{
    int windows_number = 5;
    for (int i = 0; i < windows_number; i++)
    {
        if (QueueEmpty(wQ))
        {
            return OK;
        }
        if (service_windows[i].left_occupied_cycles_count > 0)
        {
            service_windows[i].left_occupied_cycles_count--;
        }
        if (service_windows[i].category != PERSONAL)
        {
            continue;
        }
        if (!service_windows[i].left_occupied_cycles_count)
        {
            Customer tmp;
            DeQueue(wQ, &tmp);
            service_windows[i].left_occupied_cycles_count = tmp.category;
            tmp.dequeued_cycles_count = cycles_count;
            Output(&tmp);
        }
    }
    // Test(wQ);
}
Status WindowsDecrease(SqQueue *wQ, Window service_windows[])
{
    int length = QueueLength(wQ);
    while (customers_average_wait_length(length, service_windows) < 7)
    {
        if (!WindowSwitch(service_windows, OTHER))
        {
            return OK;
        }
    }
    return OK;
}

Status WindowSwitch(Window service_windows[], enum ServiceCategories category)
{
    int windows_number = 5;
    if (category == PERSONAL)
    {
        for (int i = 0; i < windows_number; i++)
        {
            if (service_windows[i].category == OTHER)
            {
                service_windows[i].category = PERSONAL;
                return OK;
            }
        }
        return ERROR;
    }
    else
    {
        int flag = -1;
        for (int i = 0; i < windows_number; i++)
        {
            if (service_windows[i].is_switchable && service_windows[i].category == PERSONAL)
            {
                if (flag != -1)
                {
                    if (service_windows[flag].left_occupied_cycles_count > service_windows[i].left_occupied_cycles_count)
                    {
                        flag = i;
                    }
                }
                else
                {
                    flag = i;
                }
            }
        }
        if (flag != -1)
        {
            service_windows[flag].category = OTHER;
            return OK;
        }
        return ERROR;
    }
}

Status Output(Customer *c)
{
    printf("%d : %d\n", c->number, c->dequeued_cycles_count - c->enqueued_cycles_count);
    return OK;
}

Status Test(SqQueue *Q)
{
    puts("");
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE)
    {
        printf("%2d(%d) ", Q->line[i].number, Q->line[i].category);
    }
    puts("");
}