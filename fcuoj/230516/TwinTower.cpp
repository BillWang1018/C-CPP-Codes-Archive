#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n1, n2, testCase=1;
    while(cin >> n1 >> n2) {
        if(!(n1 && n2)) break;
        cout << "Twin Towers #" << testCase++ << "\n";
        int t1[n1+1], t2[n2+1];
        for(int n{}; n<n1; n++) cin >> t1[n+1];
        for(int n{}; n<n2; n++) cin >> t2[n+1];

        int dp[n1+1][n2+1]{};
        for(int i=1; i<=n1; i++) {
            for(int j=1; j<=n2; j++) {
                if(t1[i] == t2[j])
                    dp[i][j] = dp[i-1][j-1]+1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        cout << "Number of Tiles : " << dp[n1][n2] << "\n";
    }
    return 0;
}