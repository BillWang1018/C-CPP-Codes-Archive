#include <iostream>
using namespace std;
int main() {
    int T, N, P;
    cin >> T;
    while(T--) {
        cin >> N >> P;
        int hartals[P], hd{};
        for(int i{}; i<P; i++) {
            cin >> hartals[i];
        }

        for(int i=1; i<=N; i++) {
            if(i%7 == 6 || i%7 == 0)
                continue;
            for(int h : hartals) {
                if(!(i%h)) {
                    hd++;
                    break;
                } 
            }
        }

        cout << hd << "\n";
    }
    return 0;
}