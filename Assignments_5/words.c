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
    char word[20];
    int count;
    struct Node *lchild, *rchild;
} Node, *Tree;

char *strprocess(char *str)
{
    char *p = str;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = *p + 'a' - 'A';
        }
        else if (*p < 'a' || *p > 'z')
        {
            *p = ' ';
        }
        p++;
    }
    return str;
}

Status InitNode(Node *N)
{
    N->count = 1;
    N->word[0] = '\0';
    N->lchild = N->rchild = NULL;
}

Status AddNode(const char *str, Node **pN)
{
    Node *N = *pN;
    if (N == NULL)
    {
        N = (Node *)malloc(sizeof(Node));
        InitNode(N);
        strcpy(N->word, str);
        *pN = N;
        return OK;
    }
    if (strcmp(str, N->word) == 0)
    {
        N->count++;
        return OK;
    }
    else if (strcmp(str, N->word) < 0)
    {
        AddNode(str, &N->lchild);
    }
    else
    {
        AddNode(str, &N->rchild);
    }
    return OK;
}

Status PrintNode(Node *N)
{
    printf("%s %d\n", N->word, N->count);
    return OK;
}

Status Traverse(Node *N, Status (*visit)(Node *))
{
    if (N->lchild)
        Traverse(N->lchild, visit);
    visit(N);
    if (N->rchild)
        Traverse(N->rchild, visit);
    return OK;
}

char *get_next_word_in_str(char *str, char *word)
{
    while (*str == ' ')
        str++;
    if (*str == '\0')
    {
        *word = '\0';
        return str;
    }
    sscanf(str, "%s", word);
    int length = strlen(word);
    return str + length;
}

int main()
{
    FILE *fp = fopen("article.txt", "r");
    Tree T = NULL;
    char str[MAXSIZE];
    while (fgets(str, MAXSIZE, fp) != NULL)
    {
        strprocess(str);
        char word[20];
        char *p = str;
        while (*p != '\0')
        {
            p = get_next_word_in_str(p, word);
            if (*word != ' ' && *word != '\0')
                AddNode(word, &T);
        }
    }

    if (T)
    {
        printf("%s ", T->word);
        if (T->rchild)
        {
            printf("%s ", T->rchild->word);
            if (T->rchild->rchild)
                printf("%s", T->rchild->rchild->word);
        }
    }
    puts("");
    Traverse(T, PrintNode);
    fclose(fp);
    return 0;
}