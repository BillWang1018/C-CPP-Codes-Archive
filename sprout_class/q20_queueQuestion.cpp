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
        unordered_map<int, int> gp; //gp[ppl] == at #? group
        cin >> N;
        for(int i=1; i<=N; i++) {
            cin >> k;
            for(int j=1; j<=k; j++) {
                cin >> p;
                gp[p] = i;
            }
        }
        // create waiting line
        queue<int> phi; // phi: empty queue
        vector<queue<int>> wtline;
        unordered_map<int, int> atline; //atline[group#] == at wtline[q?]
        
        // input commands
        int fr=0; //first of wtline
        cin >> M;
        while (M--) {
            cin >> cmd;
            if(cmd[0] == 'E') {
                cin >> p;
                if(atline[gp[p]] == 0) { // group not in line
                    wtline.push_back(phi);
                    wtline[wtline.size()-1].push(p);
                    if(gp[p]) { // p is in group (!=0)
                        atline[gp[p]] = wtline.size();
                    }
                } else { // group is in line
                    wtline[atline[gp[p]]-1].push(p);
                }
            }   
            if(cmd[0] == 'D') {
                p = wtline[fr].front();
                cout << p << '\n';
                wtline[fr].pop();
                if(wtline[fr].empty()) {// no people in the same group waiting
                    atline[gp[p]] = 0; // remove group from wtline
                    fr++; // throw away empty queue
                }
            }
        }
    }
    return 0;
}