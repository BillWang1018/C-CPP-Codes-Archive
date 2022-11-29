#include <iostream>
#include <cstdio>
using namespace std;
typedef long long int ll;
int main() {
    int N;
    while(scanf("%d", &N) != EOF) {
        if(N == 1) {
            cout << 1 << "\n";
            continue;
        }
        ll n = ((N+1)/2)-1;
        ll n_1st = 1+n*2*n;
        ll n_Nth = n_1st + (N-1)*2;

        cout << n_Nth*3 - 6 << "\n";
    }
    return 0;
}