#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 3500
#define MAXLENGTH 21
#define TRUE 1
#define FALSE 0
#define NHASH 3001
#define MULT 37
typedef struct
{
    int is_found;
    int search_time;
} Status;
typedef struct node
{
    char word[MAXLENGTH];
    struct node *next;
} hash_node;
hash_node *hash_graph[NHASH] = {NULL};
char words[MAXSIZE][MAXLENGTH];
int maxsize;
int index_head[26] = {0};
int index_size[26] = {0};
int input_dic(FILE *DIC);
Status sq_search(const char *);
Status bi_search(const char *);
Status index_search(const char *key);
void init_hash_node(hash_node *N);
unsigned int hash(const char *str);
void create_hash_graph();
Status hash_search(const char *key);
int main()
{
    FILE *DIC = fopen("dictionary3000.txt", "r");
    maxsize = input_dic(DIC);
    // for (char x = 'a'; x <= 'z'; x++)
    // {
    //     printf("%c:%d-%d:%d\n", x, index_head[x - 'a'] + 1, index_head[x - 'a'] + index_size[x - 'a'],index_size[x - 'a']);
    // }
    // printf("%d", maxsize);
    create_hash_graph();

    char str[MAXLENGTH];
    int op = 0;
    while (scanf("%s%d", str, &op) != EOF)
    {
        Status ans;
        switch (op)
        {
        case 1:
            ans = sq_search(str);
            break;
        case 2:
            ans = bi_search(str);
            break;
        case 3:
            ans = index_search(str);
            break;
        case 4:
            ans = hash_search(str);
            break;
        default:
            break;
        }
        printf("%d %d\n", ans.is_found, ans.search_time);
    }
}
int input_dic(FILE *DIC)
{
    int size_count = 0, index_count = (int)'b';
    while (fscanf(DIC, "%s", words[size_count]) != EOF)
    {
        while (words[size_count][0] >= index_count)
        {
            index_head[index_count - 'a'] = size_count;
            index_size[index_count - 'b'] = size_count - index_head[index_count - 'b'];
            index_count++;
        }
        size_count++;
    }
    while ('z' + 1 >= index_count)
    {
        if (index_count <= 'z')
            index_head[index_count - 'a'] = size_count;
        index_size[index_count - 'b'] = size_count - index_head[index_count - 'b'];
        index_count++;
    }
    return size_count;
}
Status sq_search(const char *key)
{
    Status ans = {FALSE, 0};
    for (int i = 0; i < maxsize; i++)
    {
        ans.search_time++;
        int cmp = strcmp(words[i], key);
        if (cmp >= 0)
        {
            if (cmp == 0)
                ans.is_found = TRUE;
            break;
        }
    }
    return ans;
}
Status bi_search(const char *key)
{
    Status ans = {FALSE, 0};
    int low = 0, high = maxsize - 1;
    int mid;
    while (low <= high)
    {
        ans.search_time++;
        mid = (low + high) / 2;
        int cmp = strcmp(words[mid], key);
        if (cmp > 0)
        {
            high = mid - 1;
        }
        else if (cmp == 0)
        {
            ans.is_found = TRUE;
            break;
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
    }
    return ans;
}
Status index_search(const char *key)
{
    Status ans = {FALSE, 0};
    char index_char = key[0];
    int low = index_head[index_char - 'a'], high = index_head[index_char - 'a'] + index_size[index_char - 'a'] - 1;
    int mid;
    while (low <= high)
    {
        ans.search_time++;
        mid = (low + high) / 2;
        int cmp = strcmp(words[mid], key);
        if (cmp > 0)
        {
            high = mid - 1;
        }
        else if (cmp == 0)
        {
            ans.is_found = TRUE;
            break;
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
    }
    return ans;
}
unsigned int hash(const char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}
void init_hash_node(hash_node *N)
{
    N->word[0] = '\0';
    N->next = NULL;
    return;
}
void create_hash_graph()
{
    for (int i = 0; i < maxsize; i++)
    {
        int hash_num = hash(words[i]);
        if (hash_graph[hash_num] == NULL)
        {
            hash_graph[hash_num] = (hash_node *)malloc(sizeof(hash_node));
            init_hash_node(hash_graph[hash_num]);
            strcpy(hash_graph[hash_num]->word, words[i]);
        }
        else
        {
            hash_node *p = hash_graph[hash_num];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = (hash_node *)malloc(sizeof(hash_node));
            init_hash_node(p->next);
            strcpy(p->next->word, words[i]);
        }
    }
}
Status hash_search(const char *key)
{
    int hash_num = hash(key);
    Status ans = {FALSE, 0};
    hash_node *p = hash_graph[hash_num];
    while (p != NULL)
    {
        ans.search_time++;
        if (strcmp(p->word, key) == 0)
        {
            ans.is_found = TRUE;
            break;
        }
        p = p->next;
    }
    return ans;
}