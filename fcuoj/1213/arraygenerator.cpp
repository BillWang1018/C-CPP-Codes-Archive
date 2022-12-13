#include <iostream>
using namespace std;
int main() {
    string s;
    getline(cin, s);
    cout << "[ ";
    for(int _{}; _<s.size(); _++) {
        cout << "'" << s[_] << "'" << ((_==s.size()-1)?"": ", ");
    }
    cout << " ]";
    return 0;
}