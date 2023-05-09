#include <iostream>
#include <algorithm>
#include <cmath>
#define ROUNDING_DIG 100000
using namespace std;

struct Work {
    int index;
    double days, fine, avg;
};

int main() {
    freopen("output.txt","w",stdout);
    int T, N;
    double a,b;
    cin >> T;
    while(T--) {
        cin >> N;
        int n{};
        Work works[N];
        while(N--) {
            cin >> a >> b;
            works[n++] = {n, a, b, round((b/a)*ROUNDING_DIG)/ROUNDING_DIG};
        }
        sort(works, works+n, [](Work a, Work b) {
            return (a.avg != b.avg) ? (a.avg > b.avg) : (a.index < b.index);
        });

        for(int i{}; i<n; i++) {
            cout << works[i].index;
            if(i<n-1)
                cout << " ";
        }
        if(T)
            cout << "\n\n";
    }

    return 0;
}