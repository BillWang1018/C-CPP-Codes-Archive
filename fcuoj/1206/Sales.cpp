#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, count{};
        cin >> n;
        int nums[n], sums[n];
        for(int _{}; _<n; _++)
            cin >> nums[_];

        for(int i=0; i<n; i++)
            for(int j=0; j<i; j++) 
                count += (nums[i] >= nums[j]);

        cout << count << "\n";
    }
    return 0;
}
