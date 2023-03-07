#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
int main() {
    int n, *nums;
    cin >> n;
    nums = (int*) malloc( sizeof(int) * n ); 
    for(int i{}; i<n; i++) 
        cin >> *(nums+i);

    sort(nums, nums+n);

    int i, *f,*l,*r;
    set< vector<int> > ans;
    bool hasAns = false;

    for(i=0; i<=n-3; i++) {
        f=nums+i, l=nums+i+1, r=nums+n-1;
        while( l != r ) {
            int sum = *f+*l+*r;
            if(sum < 0) l++;
            if(sum > 0) r--;
            if(sum == 0) {
                hasAns = true;
                ans.insert({*f, *l, *r});
                l++;
            }
        }
    }
    if(hasAns)
        for(auto a:ans) {
            cout << a[0] << " " << a[1] << " " << a[2] << "\n";
        }
    else
        cout << "0";

    return 0;
}