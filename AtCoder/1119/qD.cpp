#include <iostream>
#include <unordered_map>
typedef long long int ll;
using namespace std;
int main() {
    ll N, A, Q, q, iq, xq, unified=-1;
    cin >> N;
    unordered_map<ll, ll> num, zeros;
    for(ll i=1; i<=N; i++) {
        cin >> num[i];
    }
    cin >> Q;
    for(ll i=1; i<=Q; i++) {
        cin >> q;
        switch (q) {
            case 1:
                cin >> xq;
                unified = xq;
                num = zeros;
                break;
            case 2:
                cin >> iq >> xq;
                num[iq] += xq;
                break;
            case 3:
                cin >> iq;
                if(unified == -1)
                    cout << num[iq] << "\n";
                else
                    cout << num[iq]+unified << "\n";
                break;
        }
    }

    return 0;
}