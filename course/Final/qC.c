#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_NODES 505

/*
 * -> bool    : returns true if a loop is found
 *
 * v          : vertex now testing for loop
 * graph[i][j]: for every vertex j : edges connected to vertex i
 * last[i]    : index where new edge should be pushed to vertex i
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
    int T;
    int charmap[255]; // ascii to indexf
    int graph[MAX_NODES][MAX_NODES];
    int last[MAX_NODES];
    bool visited[MAX_NODES], tested[MAX_NODES];
    
    int a, b, hash;
    char str[1005], *pair;

    while (scanf("%d%*c", &T)) {
        // init all elements
        hash=0;
        memset(charmap, -1, sizeof(charmap));
        memset(graph, false, sizeof(graph));
        memset(last, 0, sizeof(last));
        memset(visited, false, sizeof(visited));
        memset(tested, false, sizeof(tested));
        // quit if 0 
        if (T == 0) break;
        // make input into graph 
        fgets(str, 1005, stdin);
        pair = strtok(str, ",");
        while (pair) {
            if (charmap[pair[0]] == -1)
                charmap[pair[0]] = hash++;
            if (charmap[pair[2]] == -1)
                charmap[pair[2]] = hash++;
            a = charmap[pair[0]], b = charmap[pair[2]];
            graph[b][last[b]++] = a;

            pair = strtok(NULL, ",");
        }
        // checking loop by starting a DFS from each vertex
        bool hasLoop = false;
        for (int i=0; i<T; i++) {
            if (!hasLoop)
                hasLoop = DFS(i, graph, last, visited, tested);
        }
        // print result
        printf("%s\n", hasLoop ? "false" : "true");
    }
    
    printf("quit");
    return 0;
}