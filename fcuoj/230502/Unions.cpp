#include <iostream>
using namespace std;

union Un {
    int i;
    float f;
};

int main() {
    union Un un;
    string str;
    char op;

    while(cin >> op) {
        if(op == 'q') {
            break;
        }
        if(op == 'i') {
            cin >> un.i;
            cout << "Integer: " << un.i;
        }
        if(op == 'f') {
            cin >> un.f;
            cout << "Float: " << to_string(un.f);
        }
        if(op == 's') {
            cin >> str;
            cout << "String: " << str;
        }

        cout << "\n";
    }

    return 0;
}