#include <iostream>
#include <algorithm>
using namespace std;

struct Ad {
    int low, high, profit;
};

int main() {
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int t{}, T, N, a, b, c, maxFloor{};
    cin >> T;
    while(T--) {
        cin >> N;
        Ad ads[N]{};
        maxFloor=0;
        for(int n{}; n<N; n++) {
            cin >> a >> b >> c;
            ads[n] = {a, a+b-1, c};
            maxFloor = max(maxFloor, ads[n].high);
        }
        sort(ads, ads+N, [](Ad a, Ad b){
            return a.high < b.high;
        });

        int dp[maxFloor+1]{};

        for(int f=1; f<=maxFloor; f++) {
            for(int i{}; i<N && ads[i].high <= f; i++) {
                dp[f] = max({dp[f], dp[f-1], ads[i].profit});
                if(ads[i].low) dp[f] = max(dp[f], dp[ads[i].low-1]+ads[i].profit);
            }
            // cout << dp[f] << " ";
        }

        cout << "Case " << ++t << ": " << dp[maxFloor] << "\n";
        
    }
    return 0;
}