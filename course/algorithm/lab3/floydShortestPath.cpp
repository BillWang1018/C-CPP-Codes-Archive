#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f 

using namespace std;

int main() {
    vector<vector<int>> graph = {
        {0, 4, INF, INF, INF, 10, INF},
        {3, 0, INF, 18, INF, INF, INF},
        {INF, 6, 0, INF, INF, INF, INF},
        {INF, 5, 15, 0, 2, 19, 5},
        {INF, INF, 12, 1, 0, INF, INF},
        {INF, INF, INF, INF, INF, 0, 10},
        {INF, INF, INF, 8, INF, INF, 0}
    };
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, 0));

    // Initialize the distance and next matrices
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
        }
    }
    // Floyd-Warshall algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = k+1;
                }
            }
        }
    }
    // Print the shortest path matrix
    cout << "Shortest path matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
    // Print the next matrix
    cout << "Next matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << next[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}