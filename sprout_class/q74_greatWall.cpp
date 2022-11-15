#include<iostream>
using namespace std;

int solve() {
    int N, n;
    cin >> N;
    if(N<=1) return N; 
    int num[N];
    for(int i=0; i<N; i++) 
        cin >> num[i];
    bool ascend = num[0]<num[1];
    int ans = 1;
    for(int i=0; i<N-1; i++) {
        if(ascend) {
            if(!(num[i] < num[i+1])) {
                ascend = false;
            }
        } else {
            if(!(num[i] > num[i+1])) {
                ascend = true;
                ans += 2;
            }
        }       
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << "\n";
    }
    return 0;
}