#include <iostream>
#include <vector>
#include <unordered_set>
typedef long long int ll;
using namespace std;
int main() {
    ll N, Q, T, A, B;
    cin >> N >> Q;
    vector<unordered_set<ll>> following(N+1);
    for (ll i=0; i<Q; i++) {
        cin >> T >> A >> B;
        switch (T) {
            case 1:
                following[A].insert(B);
                break;
            case 2:
                following[A].erase(B);
                break;
            case 3:
                if(following[A].find(B) == following[A].end() || following[B].find(A) == following[B].end()) {
                    cout << "No\n";
                } else {
                    cout << "Yes\n";
                }
                break;
        }
    }
    return 0;
}