#include <iostream>
#include <vector>
using namespace std;

int N, Q;
int data[200005][3]; //weight, min, max;
vector<int> tree[200005];
pair<int,int> dfs(int n) {
    if(tree[n].size() == 0) return {data[n][0], data[n][0]};
    for(int i : tree[n]) {
        pair<int,int> tmp = dfs(i);
        tmp.first = data[n][1] = min(data[n][0], tmp.first);
        tmp.second = data[n][2] = max(data[n][0], tmp.second);
    }
    return {data[n][1], data[n][2]};
}

int main() {
    cin >> N >> Q;
    for(int i=0; i<N-1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
    }
    for(int i=1; i<=N; i++) {
        int a;
        cin >> a;
        data[i][0] = a;
        data[i][1] = 1e9+1;
        data[i][2] = 0;
    }
    dfs(1);
    for(int i=0; i<Q; i++) {
        int a;
        cin >> a;
        cout << data[a][2]-data[a][1] << "\n";
    }

    return 0;
}