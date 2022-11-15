#include <iostream>
using namespace std;
int main() {
    int T, n, size=0;
    cin >> T;
    int stack[100005];
    while(T--) {
        cin >> n;
        if(n == 1) { // stack.push()
            cin >> n;
            stack[size++] = n;
        } else { // stack.pop()
            if(size)
                cout << stack[--size] << "\n";
            else 
                cout << "empty!\n";
        }
    }

    return 0;
}