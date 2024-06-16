#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXSTATIONS 1024
#define MAXLINES 16
#define INF INT_MAX

typedef struct
{
    char name[64];
    int transfer;
} Station;

typedef struct
{
    int line;
    int stationCount;
    Station stations[MAXSTATIONS];
} Line;

typedef struct
{
    char name[64];
    int line;
    int index;
} Node;

Line lines[MAXLINES];
Node nodes[MAXSTATIONS];
int distances[MAXSTATIONS][MAXSTATIONS];
int nodeCount = 0;
int lineCount = 0;

int getNodeIndex(const char *name, int line)
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (strcmp(nodes[i].name, name) == 0 && nodes[i].line == line)
        {
            return i;
        }
    }
    strcpy(nodes[nodeCount].name, name);
    nodes[nodeCount].line = line;
    nodes[nodeCount].index = nodeCount;
    return nodeCount++;
}

void readData(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &lineCount);
    for (int i = 0; i < lineCount; i++)
    {
        int line, stationCount;
        fscanf(file, "%d %d", &line, &stationCount);
        lines[i].line = line;
        lines[i].stationCount = stationCount;
        for (int j = 0; j < stationCount; j++)
        {
            fscanf(file, "%s %d", lines[i].stations[j].name, &lines[i].stations[j].transfer);
            int nodeIndex = getNodeIndex(lines[i].stations[j].name, line);
        }
    }
    fclose(file);
}

void buildGraph()
{
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++)
        {
            distances[i][j] = INF;
        }
    }
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < lines[i].stationCount - 1; j++)
        {
            int u = getNodeIndex(lines[i].stations[j].name, lines[i].line);
            int v = getNodeIndex(lines[i].stations[j + 1].name, lines[i].line);
            distances[u][v] = distances[v][u] = 1;
        }
    }
    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++)
        {
            if (i != j && strcmp(nodes[i].name, nodes[j].name) == 0)
            {
                distances[i][j] = distances[j][i] = 0;
            }
        }
    }
}

void dijkstra(int src, int dst)
{
    int dist[nodeCount], prev[nodeCount], visited[nodeCount];
    for (int i = 0; i < nodeCount; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int i = 0; i < nodeCount; i++)
    {
        int minDist = INF, u = -1;
        for (int j = 0; j < nodeCount; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1)
            break;
        visited[u] = 1;
        for (int v = 0; v < nodeCount; v++)
        {
            if (!visited[v] && distances[u][v] != INF && dist[u] + distances[u][v] < dist[v])
            {
                dist[v] = dist[u] + distances[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[dst] == INF)
    {
        printf("No path found\n");
        return;
    }

    int path[nodeCount], pathCount = 0;
    for (int v = dst; v != -1; v = prev[v])
    {
        path[pathCount++] = v;
    }

    printf("%s", nodes[path[pathCount - 1]].name);
    int lastLine = nodes[path[pathCount - 1]].line;
    int stationCount = 0;

    for (int i = pathCount - 1; i > 0; i--)
    {
        if (nodes[path[i - 1]].line != lastLine)
        {
            if (stationCount)
                printf("-%d(%d)-%s", lastLine, stationCount, nodes[path[i - 1]].name);
            lastLine = nodes[path[i - 1]].line;
            stationCount = 0;
        }
        else
        {
            stationCount++;
            if (i == 1)
            {
                printf("-%d(%d)-%s", lastLine, stationCount, nodes[path[i - 1]].name);
            }
        }
    }
    printf("\n");
    // system("pause");
}

int main()
{
    readData("bgstations.txt");

    buildGraph();

    char start[64], end[64];
    scanf("%s", start);
    scanf("%s", end);

    int src = -1, dst = -1;
    for (int i = 0; i < nodeCount; i++)
    {
        if (strcmp(nodes[i].name, start) == 0 && (src == -1 || nodes[i].line < nodes[src].line))
        {
            src = i;
        }
        if (strcmp(nodes[i].name, end) == 0 && (dst == -1 || nodes[i].line < nodes[dst].line))
        {
            dst = i;
        }
    }

    if (src == -1 || dst == -1)
    {
        printf("Station not found\n");
        return 1;
    }

    dijkstra(src, dst);

    return 0;
}
