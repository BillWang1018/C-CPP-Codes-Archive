#include <iostream>
using namespace std;
int main() {
    int num[] = {0,1,2};
    cout << num << '\n';
    int *l = num, *r = num+3-1;
    while(l < r) { // cool bitwise xor thing to swap(l,r)
        *l ^= *r;
        *r ^= *l;
        *l ^= *r;
        
        l++, r--;
    }
    cout << num << '\n';
    cout << num+1 << '\n';
    cout << num[2] << '\n';
}