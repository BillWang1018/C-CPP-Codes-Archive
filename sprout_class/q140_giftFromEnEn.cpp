#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    int dp[100005][3];//r, g, b
    int back = 0;
    while(T--) {
        int N;
        cin >> N;
        dp[0][0] = dp[0][1] = dp[0][2] = 1;
        for(int n=back; n < N; n++) {
            dp[n][0] = dp[n-1][0]+dp[n-1][1]+dp[n-1][2];
            dp[n][1] = 
        }
        cout << d[N][0]+d[N][1]+d[N][2];
    }
    return 0;
}