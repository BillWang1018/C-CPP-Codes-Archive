#include <iostream>
using namespace std;

char disk(int n) {
    return n+'A';
}

void hanoi(int n, int s, int e) { //start -> end with n disks
    if(n == 1) {
        cout << "Move disk " << disk(s) << " to " << disk(e) << "\n";
        return;
    }
    hanoi(n-1, s, 3-s-e);
    hanoi(1, s, e);
    hanoi(n-1, 3-s-e, e);
}

int main() {
    int N;
    cin >> N;
    hanoi(N, 0, 2);
    return 0;
}