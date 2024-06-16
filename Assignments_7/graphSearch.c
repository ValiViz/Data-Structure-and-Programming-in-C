#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

int graph[MAX_N][MAX_N]; 
int n, m; 
int deleted_vertex;

void dfs(int v, int visited[], int result[], int *index) {
    visited[v] = 1;
    result[(*index)++] = v;
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] && !visited[i]) {
            dfs(i, visited, result, index);
        }
    }
}

void bfs(int start, int visited[], int result[], int *index) {
    int queue[MAX_N], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    
    while (front < rear) {
        int v = queue[front++];
        result[(*index)++] = v;
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

void print_result(int result[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", result[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    
    scanf("%d", &deleted_vertex);
    
    int visited[MAX_N] = {0};
    int dfs_result[MAX_N], bfs_result[MAX_N];
    int index = 0;
    
    dfs(0, visited, dfs_result, &index);
    print_result(dfs_result, index);
    
    for (int i = 0; i < MAX_N; ++i) visited[i] = 0;
    index = 0;
    
    bfs(0, visited, bfs_result, &index);
    print_result(bfs_result, index);
    
    for (int i = 0; i < n; ++i) {
        graph[deleted_vertex][i] = 0;
        graph[i][deleted_vertex] = 0;
    }
    
    for (int i = 0; i < MAX_N; ++i) visited[i] = 0;
    index = 0;
    
    dfs(0, visited, dfs_result, &index);
    print_result(dfs_result, index);
    
    for (int i = 0; i < MAX_N; ++i) visited[i] = 0;
    index = 0;
    
    bfs(0, visited, bfs_result, &index);
    print_result(bfs_result, index);
    
    return 0;
}
