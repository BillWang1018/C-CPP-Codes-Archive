#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // handle T
    int T;
    cin >> T;
    for(int t=1; t<=T; t++) {
        cout << "Line #" << t << '\n';
        // vars
        int N, M, k, p;
        string cmd;

        // input grouping data
        cin >> N;
        queue<int> wtline; 
        vector<int> group(1000000, 0);
        vector<queue<int>> gqueue(N+1, queue<int>());
        vector<bool> waiting(N+1, false);
        for(int i=1; i<=N; i++) {
            cin >> k;
            for(int j=1; j<=k; j++) {
                cin >> p;
                group[p] = i;
            }
        }
        
        // input commands
        cin >> M;
        while (M--) {
            cin >> cmd;
            if(cmd[0] == 'E') {
                cin >> p;
                if(group[p] == 0) { // p not belongs to any group
                    wtline.push(-p);
                    continue;
                } else {
                    if(waiting[group[p]] == false) { // group not in line
                        waiting[group[p]] = true; // push group in line
                        wtline.push(group[p]);
                    }
                    gqueue[group[p]].push(p); // push p in group
                }
            }   
            if(cmd[0] == 'D') {
                if(wtline.front() < 0) {
                    cout << -(wtline.front()) << "\n";
                    wtline.pop();
                    continue;
                } else {
                    cout << gqueue[wtline.front()].front() << "\n";
                    gqueue[wtline.front()].pop();
                    if(gqueue[wtline.front()].empty()) { // check if groupQueue is empty
                        waiting[wtline.front()] = false; // pop group
                        wtline.pop();
                    }
                }
            }
        }
    }
    return 0;
}