#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector> // Added for std::vector

using namespace std;

// https://blog.csdn.net/hzh_0000/article/details/9468377
#define INF 0x3f3f3f3f 
#define MAXN 25
#define min(a,b) ((a) < (b) ? (a) : (b))

int solveTSP(const int start, const int n, vector<vector<int>> &dist, vector<int> &ans) {

    if (n > MAXN) {
        ans[0] = -2;
        return -2; // too many cities
    }

    if (n == 1) {
        ans[0] = start;
        return 0; // only one city, no cost
    }

    // dp[mask][i]
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> path(1 << n, vector<int>(n, -1));

    // start from empty set
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        dp[0][i] = dist[i][start];
        path[0][i] = start;
    }

    for (int sSize = 1; sSize <= n-2; sSize++) {
        for (int i = 0; i < n; i++) {
            if (i == start) continue;
            int comb = (1 << sSize) - 1;
            while (comb < (1 << n)) {
                int minCost = INF, newCost = INF;
                if (!(comb & (1 << i) || comb & (1 << start))) {
                    for (int k = 0; k < n; k++) {
                        if (comb & (1 << k)) {
                            newCost = dist[i][k] + dp[comb ^ (1 << k)][k];
                            if (newCost < minCost) {
                                minCost = newCost;
                                path[comb][i] = k;
                                dp[comb][i] = minCost;
                            }
                        }
                    }
                }
                int x = comb & -comb;
                int y = comb + x;
                comb = ((comb & ~y) / x >> 1) | y;
            }
        }
    }

    int minCost = INF, newCost = INF, lastCity = -1;
    for (int k = 0; k < n; k++) {
        if (k == start) continue;

        int comb = ((1 << n) - 1) ^ (1 << start) ^ (1 << k);
        for (int i = 0; i < n; i++)
            if (i != start && i != k)
                comb |= (1 << i);
        newCost = dist[start][k] + dp[comb][k];
        if (newCost < minCost) {
            minCost = newCost;
            lastCity = k;
        }
    }
    if (lastCity == -1) {
        ans[0] = -1;
        return -1;
    }

    int mask = ((1 << n) - 1) ^ (1 << start); 
    int current = lastCity, index = 0;
    while (mask) {
        ans[index++] = current;
        mask ^= (1 << current);
        current = path[mask][current];
    }
    ans[index++] = start;
    reverse(ans.begin(), ans.begin() + index);

    return minCost;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[j][i]);
            if (dist[j][i] == -1) {
                dist[j][i] = INF;
            }
        }
    }

    solveTSP(0, n, dist, ans);

    if (ans[0] < 0) {
        printf("%d\n", ans[0]);
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d ", ans[i] + 1);
        }
        printf("%d\n", ans[0] + 1);
    }

    return 0;
}