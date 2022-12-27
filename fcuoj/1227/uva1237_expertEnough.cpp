#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    while(T--) {

        int D, L, H, Q, P;
        cin >> D;
        string M, brand[D];
        int lowP[D];
        int highP[D];

        for(int i=0; i<D; i++) {
            cin >> M >> L >> H;
            brand[i] = M;
            lowP[i] = L;
            highP[i] = H;
        }

        cin >> Q;
        while(Q--) {
            cin >> P;
            string ans = "UNDETERMINED";
            bool flag = false;
            for(int i=0; i<D; i++) {
                if(lowP[i] <= P && P <= highP[i])
                    if(!flag) {
                        flag = true;
                        ans = brand[i];
                    } else {
                        ans = "UNDETERMINED";
                        break;
                    }
            }
            cout << ans << '\n';
        }
        cout << '\n';
    }
    return 0;
}
/*-.
-----............... 1 5
..------............ 3 8
....----------...... 5 14
.....------......... 6 11
.......---------.... 8 16
............-------- 13 20


-----............... 1 5
..------............ 3 8
.....------......... 6 11
....----------...... 5 14
.......---------.... 8 16
............-------- 13 20
*/