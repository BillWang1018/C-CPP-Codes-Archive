#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n;
    while(cin >> n) {
        int num[n+5]={};
        bool check[n+5]={};
        bool result = true;
        for(int i=0; i<n; i++) {
            cin >> num[i];
        }
        for(int i=0; i<n-1; i++) {
            check[abs(num[i]-num[i+1])] = true;
        }
        for(int i=1; i<n; i++) {
            if(check[i]) continue;
            result = false;
            break;
        }
        cout << (result ? "Jolly" : "Not jolly") << "\n";
    }
    return 0;
}