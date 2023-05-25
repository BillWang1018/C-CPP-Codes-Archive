#include <iostream>
#include <vector>
using namespace std;
int main() {
    int N, M, a, b;
    while(cin >> N) {
        if(!N) break;
        vector< vector<int> > tree(N);
        vector<int> color(N);
        cin >> M;
        for(int m{}; m<M; m++) {
            cin >> a >> b;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        color[0] = 1;

        bool flag = true; // if case is bicolorable
        for(int i{}; i<M; i++) {
            bool hasColorA, hasColorB;
            hasColorA = hasColorB = false;
            
            if(color[i] == 1)
                hasColorA = true; 
            if(color[i] == 2) 
                hasColorB = true;

            for(auto child: tree[i]) {
                if(color[child] == 1) hasColorA = true;
                if(color[child] == 2) hasColorB = true;
            }

            // cout << i << " :: " << hasColorA << " | " << hasColorB << endl;
            if(hasColorA && hasColorB) // not bicolorable
                flag = false;
            else if(hasColorA) // child has A, self -> B
                color[i] = 2;
            else   // child has B or no color, self -> A
                color[i] = 1;
        }
        if(flag) 
            cout << "BICOLORABLE.\n";
        else
            cout << "NOT BICOLORABLE.\n";
    }
    return 0;
}
