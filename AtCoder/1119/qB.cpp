#include <iostream>
using namespace std;

bool check(int h, int m) {
    int h2 = h - h%10 + m/10;
    int m2 = (h%10)*10 + m%10;
    if(h2 <= 23 && m2 <= 59)
        return true;
    return false;
}

int main() {
    int H, M;
    cin >> H >> M;
    while(!check(H, M)) {
        M++;
        if(M >= 60)
            H++, M=0;
        if(H >= 24)
            H=0;
    }
    cout << H <<  " " << M;
    return 0;
}