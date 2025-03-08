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
    int chartokey[MAX_NODES]; // ascii to indexf
    char keytochar[MAX_NODES];
    int graph[MAX_NODES][MAX_NODES];
    int last[MAX_NODES];
    bool visited[MAX_NODES], tested[MAX_NODES];
    
    int a, b, hash;
    char str[1005], *pair;

    while (scanf("%d%*c", &T)) {
        // init all elements
        bool hasLoop = false;
        hash=0;
        memset(chartokey, -1, sizeof(chartokey));
        memset(graph, false, sizeof(graph));
        memset(last, 0, sizeof(last));
        memset(visited, false, sizeof(visited));
        memset(tested, false, sizeof(tested));
        // quit if 0 
        if (T == 0) break;
        // make input into graph 
        fgets(str, 1005, stdin);
        pair = strtok(str, ",");
        // no prerequisites (special case)
        if (pair[1] == '\n') {
            pair = NULL;
            for (int i=0; i<T; i++) {
                printf("%d ", i);
            }
            printf("\n");
            continue;
        }
        while (pair) {
            if (chartokey[pair[2]] == -1) {
                keytochar[hash] = pair[2];
                chartokey[pair[2]] = hash++;
            }
            if (chartokey[pair[0]] == -1) {
                keytochar[hash] = pair[0];
                chartokey[pair[0]] = hash++;
            }
            a = chartokey[pair[0]], b = chartokey[pair[2]];
            // check if self cycle exists
            for (int j=0; j<last[b]; j++) {
                if (graph[b][j] == a) {
                    hasLoop = true;
                    break;
                }
            }
            if (!hasLoop)
                graph[b][last[b]++] = a;
            else 
                break;

            pair = strtok(NULL, ",");
        }
        // checking loop by starting a DFS from each vertex
        for (int i=0; i<T; i++) {
            if (!hasLoop)
                hasLoop = DFS(i, graph, last, visited, tested);
        }
        // print result
        if (!hasLoop) {
            memset(visited, false, sizeof(visited));
            // self
            for (int i=0; i<T; i++) {
                if (!visited[i])
                    printf("%c ", keytochar[i], i);
                visited[i] = true;
                // edges of i
                for (int j=0; j<last[i]; j++) {
                    if (!visited[graph[i][j]])
                        printf("%c ", keytochar[graph[i][j]], graph[i][j]);
                    visited[graph[i][j]] = true;
                }
            }
            printf("\n");
        } else {
            printf("error\n");
        }
    }
    
    printf("quit");
    return 0;
}