#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_NODES 505

/*
 * v          : vertex now testing for loop
 * graph[i][j]: edges connected to vertex i
 * last[i]    : index where new edge should be pushed
 * visited[i] : if the vertex has been visited
 * tested[i]  : if every edges has completed DFS (loop check)
 */

bool DFS(int v, int (*graph)[MAX_NODES], int *last, bool *visited, bool *tested) {
    // printf("DFS: %d\n", v);
    if (tested[v]) return false;
    if (visited[v]) return true;

    visited[v] = true;
    for (int i=0; i<last[v]; i++) {
        if (DFS(graph[v][i], graph, last, visited, tested)) 
            return true;
    }
    tested[v] = true;
    return false;
}

int main() {
    int T, N;
    int graph[MAX_NODES][MAX_NODES];
    int last[MAX_NODES];
    bool visited[MAX_NODES], tested[MAX_NODES];
    memset(graph, false, sizeof(graph));
    memset(last, 0, sizeof(last));
    memset(visited, false, sizeof(visited));
    memset(tested, false, sizeof(tested));
    
    int a, b;
    scanf("%d %d", &T, &N);
    for (int i=0; i<N; i++) {
        scanf("%d %d", &a, &b);
        graph[b][last[b]++] = a;
    }

    bool hasLoop = false;
    for (int i=0; i<T; i++) {
        if (!hasLoop)
            hasLoop = DFS(i, graph, last, visited, tested);
    }

    printf("%s\n", hasLoop ? "false" : "true");

    return 0;
}