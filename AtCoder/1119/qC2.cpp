#include <iostream>
#include <vector>
using namespace std;
int main() {
    int N, Q, A, B, T;
    cin >> N >> Q;
    bool following[N+5][N+5] = {};
    for (int i=1; i<=Q; i++) {
        cin >> T >> A >> B;
        if(T==1) 
            following[A][B] = true;
        if(T==2)
            following[A][B] = false;
        if(T==3)
            if(following[A][B] && following[B][A]) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
    }
    return 0;
}