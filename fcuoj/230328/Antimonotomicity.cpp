#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int T,N,num;
    cin >> T;
    while(T--) {
        vector<int> fred;
        cin >> N;
        for(int i{}; i<N; i++) {
            cin >> num;
            fred.push_back(num);
        }

        int ans=1;
        for(int i=0; i<N-1; i++) {
            if(ans%2) { // a > b
                if(fred[i] > fred[i+1])
                    ans++;
            } else { // a < b
                if(fred[i] < fred[i+1])
                    ans++;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}