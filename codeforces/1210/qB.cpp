#include <iostream>
#include <cmath>
typedef long long ll;
using namespace std;

ll findYLK(ll i) {
    ll sum{};
    while(i != 1) {
        if(i%2) {
            i *= 3;
            i++;
        } else {
            i /= 2;
        }
        sum++;
    }
    return sum+1;
}

int main() {
    ll n, A, B;
    cin >> n;
    while(n--) {
        cin >> A >> B;
        ll ans{}, a, b;

        if(A > B)
            a=B, b=A;
        else 
            a=A, b=B;

        for (ll i=a; i<=b; i++) {
            ans = max(ans, findYLK(i));
        }
        cout << A << " " << B << " " << ans << (n ? "\n" : "");
    }

    return 0;
}