#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// https://blog.csdn.net/hzh_0000/article/details/9468377
#define INF 0x3f3f3f3f 
#define MAXN 25
#define min(a,b) ((a) < (b) ? (a) : (b))

int solveTSP(const int start, const int n, int **dist, int *ans) {

    if (n > MAXN) {
        ans[0] = -2;
        return -2; // too many cities
    }

    // dp[mask][i] 
    int **dp = new int*[1 << n];
    int **path = new int*[1 << n];
    for (int i = 0; i < (1 << n); i++)
        dp[i] = new int[n];
    for (int i = 0; i < (1 << n); i++)
        path[i] = new int[n];
    
    for (int i = 0; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = INF;
            
    // start from empty set
    for (int i = 0; i < n; i++) {
        // skip the starting point
        if (i == start) continue;
        // set the distance from start to i
        //printf("test: update min path dp[S{ %d }][i: %d] = %d\n", 0, i, dist[i][start]);
        dp[0][i] = dist[i][start];
        path[0][i] = start; // set the parent of i to start
    }

    for (int sSize = 1; sSize <= n-2; sSize++) {
        for (int i = 0; i < n; i++) {
            // skip the starting point
            if (i == start) continue;
            // find the minimum cost in set to reach i from k
            int comb = (1 << sSize) - 1;
            while (comb < (1 << n)) {
                int minCost = INF, newCost = INF;
                // skip the starting point and i
                if (!(comb & (1 << i) || comb & (1 << start))) {
                    // choose k from the set
                    for (int k = 0; k < n; k++) {
                        // check if k is in the set
                        if (comb & (1 << k)) {
                            // [comb ^ (1 << k)]: remove k from the set
                            //printf("test: (i,k) = (%d,%d); sSize = %d; comb = %d\n", i,k,sSize,comb);
                            newCost = dist[i][k] + dp[comb ^ (1 << k)][k];
                            if (newCost < minCost) {
                                minCost = newCost;
                                path[comb][i] = k; // set the parent of i to k
                                dp[comb][i] = minCost;
                            }
                        }
                    }
                    //printf("test: update min path dp[S{ %d }][i: %d] = %d\n", comb, i, minCost);
                }
                // get the next combination (bits are magic bruh :))
                int x = comb & -comb;
                int y = comb + x;
                comb = ((comb & ~y) / x >> 1) | y;
            }
        }
    }

    // find the minimum cost
    int minCost = INF, newCost = INF, lastCity = -1;
    for (int k = 0; k < n; k++) {
        // skip the starting point
        if (k == start) continue;

        int comb = ((1 << n) - 1) ^ (1 << start) ^ (1 << k); // remove start and k from the set
        for (int i = 0; i < n; i++)
            if (i != start && i != k)
                comb |= (1 << i);
        newCost = dist[start][k] + dp[comb][k];
        if (newCost < minCost) {
            minCost = newCost;
            lastCity = k;
        }
    }
    // check if there is a solution
    if (lastCity == -1) {
        ans[0] = -1; // no solution found
        return -1;
    }
    
    //printf("test: minCost = %d\n", minCost);

    // find the path
    int mask = ((1 << n) - 1) ^ (1 << start); 
    int current = lastCity, index = 0;
    while (mask) {
        ans[index++] = current;
        //printf("test: mask = %d; current = %d\n", mask, current);
        // remove current from the set
        mask ^= (1 << current);
        current = path[mask][current];
    }
    ans[index++] = start; // add the starting point to the path
    reverse(ans, ans + index); // reverse the path

    // free the memory
    for (int i = 0; i < (1 << n); i++)
        delete[] dp[i];
    delete[] dp;
    for (int i = 0; i < (1 << n); i++)
        delete[] path[i];
    delete[] path;

    return minCost;
}

int main() {
    // total of N cities
    int n;
    scanf("%d", &n);
    
    // distance matrix & answer array
    int **dist, *ans;
    dist = new int*[n];
    for (int i = 0; i < n; i++)
        dist[i] = new int[n];
    ans = new int[n];
    
    // EXAMPLE DISTANCE MATRIX (4 CITIES) PREDICTED ANS = 35
    /*
    n = 4;
    dist[0][0] = 0; dist[0][1] = 10; dist[0][2] = 15; dist[0][3] = 20;
    dist[1][0] = 5; dist[1][1] = 0; dist[1][2] = 9; dist[1][3] = 10;
    dist[2][0] = 6; dist[2][1] = 13; dist[2][2] = 0; dist[2][3] = 12;
    dist[3][0] = 8; dist[3][1] = 8; dist[3][2] = 9; dist[3][3] = 0;
    */
    
    
    // read the distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[j][i]);
            if (dist[j][i] == -1) {
                dist[j][i] = INF; // set the distance to INF if there is no path
            }
        }
    }


    // solve the TSP problem and store the result in ans
    // ans[0] = -1 means no solution found
    solveTSP(0, n, dist, ans);

    // print the result
    // answer required in 1-based index
    if (ans[0] < 0) {
        printf("%d\n", ans[0]);
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d ", ans[i]+1);
        }
        // back to the starting point
        printf("%d\n", ans[0]+1);
    }

    // free the memory
    for (int i = 0; i < n; i++)
        delete[] dist[i];
    delete[] dist;
    delete[] ans;

    return 0;
}