#include <iostream>
using namespace std;
int main() {
    int a,b,carry, ans;
    while(cin >> a >> b) {
        if(!a && !b)
            break;
        carry = ans = 0;
        while(a || b) {
            carry = (a%10+b%10+carry)/10;
            if(carry) ans++;
            a/=10, b/=10;
        }
        cout << ((ans)? to_string(ans) : "No") << " carry operation" << ((ans > 1)? "s" : "") << ".\n";
    }
    return 0;
}