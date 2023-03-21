#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int r, vivo;
        cin >> r;
        int s[r];
        for(int i=0; i<r; i++) {
            cin >> *(s+i);
        }
        sort(s, s+r);
        if(r%2) {
            vivo = *(s+(r/2));
        } else {
            vivo = (*(s+(r/2)) + *(s+(r/2-1))) / 2;
        }
        int ans{};
        for(int i=0; i<r; i++) {
            // cout << "test: " << *(s+i) << "\n";
            ans += abs(vivo - *(s+i));
        }
        cout << ans << "\n";
    }
    return 0;
}
