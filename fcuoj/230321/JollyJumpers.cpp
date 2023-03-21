#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int main() {
    int n;
    while(cin >> n) {
        map<int, bool> check;
        bool ans = true;
        int nums[n];
        for(int i=0; i<n; i++) {
            cin >> nums[i];
        }
        for(int i=0; i<n-1; i++) {
            check[abs(nums[i+1] - nums[i])] = true;
        }
        for(int i=1; i<n; i++) {
            if(check[i]) continue;
            ans = false;
        }
        cout << (ans? "Jolly":"Not jolly") << "\n";
    }
    return 0;
}