CreateTree:
typedef struct Node
{
    int num;
    int passenger volume;
    struct Node *child1, *child2, *child3;
} Node;
Node *num_search[MAXSIZE];
Node* boarding_gates[MAXSIZE];
Node* adjusted_boarding_gates[MAXSIZE];
qsort(adjusted_boarding_gates);
