#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 110
typedef int Status;

typedef struct Node
{
    char from;
    char to;
    struct Node *next;
    Status Encoded;
} Node;

Status NodeAdd(Node **rear, char c)
{
    Node *now = *rear;
    now->next = (Node *)malloc(sizeof(Node));
    now->next->from = c;
    now->next->Encoded = 0;
    *rear = now->next;
}

Status ListTraverse(Node **head)
{
    Node *tmp = *head, *now = tmp;
    char from = tmp->from;
    tmp->Encoded = TRUE;
    for(int i = 0; i < from; i++)
    {
        now = now->next;
        if(now->Encoded) i--;
    }
    tmp->to = now->from;
    *head = now;
    return OK;
}

Status CodeList(Node *head, char code[])
{
    Node *now = head;
    char from, to;
    do
    {
        from = now->from;
        to = now->to;
        code[from] = to;
        now = now->next;
    } while (now != head);
    return OK;
}

int main()
{
    int Involved[127] = {0};
    char c;
    scanf("%c", &c);
    Involved[c] = 1;
    Node *head, *rear;
    head = (Node *)malloc(sizeof(Node));
    head->from = c;
    head->Encoded = 0;
    rear = head;
    while (scanf("%c", &c) != EOF)
    {
        if ((!Involved[c]) && c != '\n')
        {
            Involved[c] = 1;
            NodeAdd(&rear, c);
        }
    }
    for(c = 32; c <= 126; c++)
    {
        if(!Involved[c])
        {
            Involved[c] = 1;
            NodeAdd(&rear, c);
        }
    }
    rear->next = head;
    Node *now = head;
    for (int i = 32; i < 126; i++)
        ListTraverse(&now);
    now->to = head->from;
    char code[127];
    CodeList(head, code);
    FILE *IN = fopen("in.txt", "r");
    FILE *OUT = fopen("in_crpyt.txt", "w");
    while(fscanf(IN, "%c", &c) != EOF)
    {
        if(c >= 32 && c <= 126)
            fprintf(OUT, "%c", code[c]);
        else
            fprintf(OUT, "%c", c);
    }

    return 0;
}