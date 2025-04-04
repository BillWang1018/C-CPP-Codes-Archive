#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x3f3f3f3f

void solveTSP(const int start, const int n, const int **dist, int *ans) {
    int **dp = new int*[1 << n];
    int **parent = new int*[1 << n]; // Parent array to track the path
    for (int i = 0; i < (1 << n); i++) {
        dp[i] = new int[n];
        parent[i] = new int[n];
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
            parent[i][j] = -1; // Initialize parent to -1
        }
    }

    // Initialize dp for the starting city
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        dp[1 << i][i] = dist[start][i];
        parent[1 << i][i] = start; // Start from the starting city
    }

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) || i == start) continue; // Skip if i is not in the set or is the start
            for (int k = 0; k < n; k++) {
                if (k == i || !(mask & (1 << k))) continue; // Skip if k is not in the set or is the same as i
                int newCost = dp[mask ^ (1 << i)][k] + dist[k][i];
                if (newCost < dp[mask][i]) {
                    dp[mask][i] = newCost;
                    parent[mask][i] = k; // Record the city that led to city i
                }
            }
        }
    }

    // Find the minimum cost to return to the starting city
    int mask = (1 << n) - 1;
    int minCost = INF, lastCity = -1;
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        int cost = dp[mask][i] + dist[i][start];
        if (cost < minCost) {
            minCost = cost;
            lastCity = i;
        }
    }

    // Reconstruct the path
    vector<int> path;
    int currentCity = lastCity;
    while (mask) {
        path.push_back(currentCity);
        int nextCity = parent[mask][currentCity];
        mask ^= (1 << currentCity);
        currentCity = nextCity;
    }
    path.push_back(start); // Return to the starting city

    // Print the path
    reverse(path.begin(), path.end());
    for (int city : path) {
        printf("%d ", city);
    }
    printf("\n");

    // Free memory
    for (int i = 0; i < (1 << n); i++) {
        delete[] dp[i];
        delete[] parent[i];
    }
    delete[] dp;
    delete[] parent;
}

int main() {
    // Example distance matrix (4 cities)
    const int n = 4;
    const int *dist[4] = {
        new int[4]{0, 10, 15, 20},
        new int[4]{10, 0, 35, 25},
        new int[4]{15, 35, 0, 30},
        new int[4]{20, 25, 30, 0}
    };
    int ans[n]; // Array to store the answer
    solveTSP(0, 4, dist, ans); // Example call to solveTSP function

    for(int i = 0; i < n; i++) {
        delete[] dist[i]; // Free the distance matrix memory
    }
    return 0;
}