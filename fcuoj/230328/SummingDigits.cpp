#include <iostream>
using namespace std;

void sumDig(int *n) {
    int total{};
    while(*n) {
        total += (*n%10);
        *n /= 10;
    }
    *n = total;
}

int main() {
    int n;
    while(cin >> n) {
        if(!n) break;
        while(n >= 10)
            sumDig(&n);
        cout << n << "\n";
    }
    return 0;
}