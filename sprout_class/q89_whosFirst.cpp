#include<iostream>
#include<vector>
#include<algorithm>
#define C first
#define E second
using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<pair<int,int>> data;
    for(int i=0; i<N; i++) {
        int c, e;
        cin >> c >> e;
        data.push_back({c,e});
    }
    sort(data.begin(), data.end());

    int tc, end; //total cook time, end time of last person 
    tc = end = 0;
    for(int i=0; i<N; i++) {
        tc += data[i].C;
        end = max(end, tc+data[i].E);
    }
    cout << end << "\n";
    
    return;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}