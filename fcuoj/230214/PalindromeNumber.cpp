#include <iostream>
using namespace std;
int main() {
    string s;
    cin >> s;
    int len = s.size();
    for(int i=0; i<len/2; i++) {
        if(s[i] != s[len-i-1]) {
            cout << "false";
            return 0;
        }
    }
    cout << "true";
    return 0;
}