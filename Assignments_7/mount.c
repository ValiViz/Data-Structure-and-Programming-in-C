#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_E 1000

typedef struct Edge {
    int id, u, v;
} Edge;

int n, e;
Edge edges[MAX_E];
int adj[MAX_N][MAX_N];
int visited[MAX_N];
int path[MAX_E];
int path_len;

void dfs(int u, int target) {
    if (u == target) {
        for (int i = 0; i < path_len; i++) {
            printf("%d", path[i]);
            if (i < path_len - 1) {
                printf(" ");
            }
        }
        printf("\n");
        return;
    }
    visited[u] = 1;
    for (int i = 0; i < e; i++) {
        if ((edges[i].u == u && !visited[edges[i].v]) || (edges[i].v == u && !visited[edges[i].u])) {
            int next = (edges[i].u == u) ? edges[i].v : edges[i].u;
            path[path_len++] = edges[i].id;
            dfs(next, target);
            path_len--;
        }
    }
    visited[u] = 0;
}

int compare_edges(const void *a, const void *b) {
    return ((Edge *)a)->id - ((Edge *)b)->id;
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i < e; i++) {
        int id, u, v;
        scanf("%d %d %d", &id, &u, &v);
        edges[i].id = id;
        edges[i].u = u;
        edges[i].v = v;
    }
    
    qsort(edges, e, sizeof(Edge), compare_edges);

    memset(visited, 0, sizeof(visited));
    path_len = 0;

    dfs(0, n - 1);

    return 0;
}
