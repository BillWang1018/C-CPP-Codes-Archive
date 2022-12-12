#include <iostream>
using namespace std;
int main() {
    long long int n, m, x;
    cin >> n >> m >> x;
    cout << (n/x + (n%x!=0)) * (m/x + (m%x!=0));
    return 0;
}