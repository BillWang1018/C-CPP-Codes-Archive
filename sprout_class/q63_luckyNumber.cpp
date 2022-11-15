
#include <iostream>
#include <vector>
using namespace std;

int T,k;
vector<int> num, buf;
vector<bool> u;

void dfs(int layer) {
    //print
    if(layer == 6) {
        for(int i=0; i<6; i++) {
            cout << num[buf[i]] << " \n"[i==5];
        }
        return;
        } 
        if(buf.back() == k-1) return;
    for(int i=0; i<k; i++) {
        if(!u[i]) {
            buf.push_back(i);
            u[i] = true;
            dfs(layer+1);
            buf.pop_back();
            u[i] = false;
        }
    }
}

int main() {
    cin >> T;
    while (T--) {
        cin >> k;
        num.clear(), u.clear(), buf.clear();
        for(int i=0; i<k; i++) {
            int n;
            cin >> n;
            num.push_back(n);
            u.push_back(false);
        }
        dfs(0);
    }
    return 0;
}