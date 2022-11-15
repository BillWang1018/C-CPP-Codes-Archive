#include <iostream>
#include <vector>
#define MAX 10005
using namespace std;

vector<int> tree[MAX];
vector<bool> visited;
vector<int> sbtSize;
vector<int> maxsbt;

void DFS(int r) {
    visited[r] = true;
    for(int i : tree[r]) {
        if(!visited[i]) {
            DFS(i);
            sbtSize[r] += sbtSize[i];
            maxsbt[r] = max(maxsbt[r], sbtSize[i]);
        }
    }
}

int findAns(int N) {
    int cost, minCost=MAX, ans=-1;
    for(int i=0; i<N; i++) {
        cost = max(maxsbt[i], N-sbtSize[i]);
        if(minCost > cost) {
            minCost = cost;
            ans = i;
        }
    }
    return ans;
}

int main() {
    int T, N;
    cin >> T;
    while(T--) {
        cin >> N;
        // ini
        for(int i=0; i<N; i++)
            tree[i].clear();
        visited = vector<bool>(N, 0);
        sbtSize = vector<int>(N, 1);
        maxsbt = vector<int>(N);

        for(int i=0; i<N-1; i++) {
            int a,b;
            cin >> a >> b;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        DFS(0);
        cout << findAns(N) << '\n';
    }
    return 0;
}       