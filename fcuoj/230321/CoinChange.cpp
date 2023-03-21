#include <iostream>
#include <cmath>
using namespace std;


int main() {
    int n;
    long long dp[8000]{};
    int coins[] = {1,5,10,25,50};
    dp[0] = 1;
    for(int c: coins) {
        for(int i=1; i<8000; i++) {
            if(c > i) continue;
            dp[i] += dp[i-c];
        }
    }

    while(cin >> n)
        cout << dp[n] << "\n";
    
    return 0;
}