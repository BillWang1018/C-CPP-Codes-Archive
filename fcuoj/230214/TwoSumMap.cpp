#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    int n, target;
    cin >> n;
    int nums[n];
    unordered_map<int,int> numToIndex;
    for(int i{}; i<n; i++) {
        int a;
        cin >> a;
        numToIndex[a] = i;
        nums[i] = a;
    }
    cin >> target;

    for(int i{}; i<n; i++) {
        if(nums[i] > target/2) continue;
        if(numToIndex.find(target - nums[i]) != numToIndex.end()) {
            cout << i << " " << numToIndex[target - nums[i]];
            return 0;
        }
    }

    return 0;
}