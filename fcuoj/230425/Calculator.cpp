#include <iostream>
#include <cmath>
using namespace std;

long long toDecimal(string str, int base) {
    long long num=0;
    for(int i=0; i<str.size(); i++) {
        int n = str[str.size()-1-i];
        if(n >= '0' && n <= '9') n -= '0';
        if(n >= 'A' && n <= 'F') n -= ('A'-10);
        num += n * round(pow(base, i));
    }
    return num;
}

int main() {
    string digs = "0123456789ABCDEF";
    string str, sol;
    int bfr, aft;
    while(cin >> str) {
        sol.clear();
        cin >> bfr >> aft;
        long long num = toDecimal(str, bfr);
        while(num) {
            sol.push_back(digs[num%aft]);
            num /= aft;
        }
        // sol = string(sol.rbegin(), sol.rend());
        for(int i=6; i>=0; i--) {
            if(i>=sol.size()) {
                cout << '0';
                continue;
            }
            cout << sol[i];
        }
        cout << '\n';
    }
    return 0;
}