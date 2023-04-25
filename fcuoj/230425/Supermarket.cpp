#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct good {
    int c; //cost
    int d; //expired date
};

int main() {
    int N;
    while(cin >> N) {
        if(!N) {
            cout << 0;
            continue;
        }

        vector<good> v;
        int c, d;
        for(int _{}; _<N; _++) {
            cin >> c >> d;
            v.push_back({c, d});
        }
        sort(v.begin(), v.end(), [](good a, good b){
            return (a.d == b.d) ? (a.c > b.c) : (a.d < b.d);
        });

        int day=1, dp[N]{};
        dp[0] = v[0].c;
        for(int i=0; i<v.size(); i++) {
            
        }

    

        cout << sum << "\n";
    }
    return 0;
}