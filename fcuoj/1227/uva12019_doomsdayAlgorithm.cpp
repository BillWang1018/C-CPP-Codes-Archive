#include <iostream>
using namespace std;

const int firstOfMonth[] = {0, 6, 2, 2, 5, 7, 3, 5, 1, 4, 6, 2, 4};

int main() {
    int N, M, D;
    cin >> N;
    while(N--) {
        cin >> M >> D;
        string intToDate[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        cout << intToDate[(firstOfMonth[M] + D%7 - 1) % 7] << '\n';
    }
    return 0;
}