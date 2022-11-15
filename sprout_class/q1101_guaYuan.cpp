#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<int> tree[MAXN];
vector<int> color(MAXN, -1);
int T, n, m;

bool dfs(int p) {
    //printf("dfs(%d)\n", p);
    // -1: no, 0, 1
    if(color[p] == -1) color[p] = 0;
    for(int i : tree[p]) {
        //printf("i: %d\tcolor: %d\n", i, color[i]);
        if(color[i] == -1) {
            color[i] = (color[p] == 0) ? 1 : 0;
            dfs(i);
        } else if(color[i] == color[p]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> T;
    while(T--) {
        cin >> n >> m;
        for(int i=0; i<n; i++)
            color[i] = -1;
        for(int i=0; i<n; i++)
            tree[i].clear();
        for(int i=0; i<m; i++) {
            int a,b;
            cin >> a >> b;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        for(int p=0; p<n; p++) {
            if(!dfs(p)) { //isNormal?
                cout << "RAINBOW.\n";
                break;
            }
            if(p == n-1)
                cout << "NORMAL.\n";
        }

    } 
    return 0;
}