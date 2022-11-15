#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int K, Q;
    vector<int> v;
    cin >> K >> Q;
    for(int q=0; q<Q; q++) {
        int n;
        string cmd;
        cin >> cmd;
        if(cmd == "Add") {
            cin >> n;
            v.push_back(n);
        }
        if(cmd == "Remove") {
            v.erase(v.begin()+(v.size())/2);
        }
        if(cmd == "Mod") {
            for(int i=0; i<v.size(); i++) {
                v[i] %= K;
            }
        }
        if(cmd == "Reverse") {
            reverse(v.begin(), v.end());
        }
    }
    for(int i=0; i<v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}
//3 0 4 
//4 0 1 1 2