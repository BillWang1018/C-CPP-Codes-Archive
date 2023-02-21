#include <iostream>
using namespace std;
int main() {
    int n, target;
    cin >> n;
    int nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];
    cin >> target;

    for(int i=0; i<n; i++) {
        if(nums[i] > target/2) {
            continue;
        }

        for(int j=0; j<n; j++) {
            if(nums[i] + nums[j] == target) {
                cout << i << " " << j;
                return 0;
            }
        }
    }

    return 0;
}