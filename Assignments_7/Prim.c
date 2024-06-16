#include <stdio.h>
#include <stdlib.h>

#define MAXVER 512

typedef struct {
    int id, u, v, weight;
} Edge;

int parent[MAXVER];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void union_set(int u, int v) {
    parent[find(u)] = find(v);
}

int compareWeight(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

int compareID(const void *a, const void *b) {
    int *idA = (int *)a;
    int *idB = (int *)b;
    return *idA - *idB;
}

void Kruskal(Edge edges[], int n, int e, int *minWeight, int mstEdges[]) {
    int edgeCount = 0;
    *minWeight = 0;

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    qsort(edges, e, sizeof(Edge), compareWeight);

    for (int i = 0; i < e && edgeCount < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            union_set(u, v);
            *minWeight += edges[i].weight;
            mstEdges[edgeCount++] = edges[i].id;
        }
    }

    qsort(mstEdges, edgeCount, sizeof(int), compareID);
}

int main() {
    int n, e;
    scanf("%d %d", &n, &e);

    Edge edges[e];
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d %d", &edges[i].id, &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    int minWeight;
    int mstEdges[e];

    Kruskal(edges, n, e, &minWeight, mstEdges);

    printf("%d\n", minWeight);
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", mstEdges[i]);
    }
    printf("\n");

    return 0;
}
