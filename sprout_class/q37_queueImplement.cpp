#include <iostream>
#define MAX 100005
using namespace std;
int main() {
    int T, n, h=0, b=0;
    int queue[MAX];
    cin >> T;
    while(T--) {
        cin >> n;
        if(n==1) { // queue.push()
            cin >> n;
            ++b %= MAX;
            queue[b] = n;
        } else { // queue.pop()
            if(h == b)
                cout << "empty!\n";
            else {
                ++h %= MAX;
                cout << queue[h] << "\n";
            }
        }
    }
    return 0;
}