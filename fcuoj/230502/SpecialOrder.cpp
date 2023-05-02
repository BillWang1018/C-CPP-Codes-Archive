#include <iostream>
#include <algorithm>
using namespace std;

struct Number {
    int num;
    int isOdd;
    int mod;
};

int main() {
    int N, M, n;
    while(cin >> N >> M) {
        if(!N && !M) {
            cout << "0 0";
            break;
        }
        Number nums[N];
        for(int i=0; i<N; i++) {
            cin >> n;
            nums[i] = {n, n%2, n%M};
        }

        sort(nums, nums+N, [&](Number a, Number b) -> bool {
            if (a.mod != b.mod) {
                return a.mod < b.mod;
            } else {
                if (a.isOdd != b.isOdd) {
                    return a.isOdd;
                } else if (a.isOdd) { // 1 - odd
                    return a.num > b.num;
                } else if (!a.isOdd) { // 0 - even
                    return a.num < b.num;
                }
            }
        });

        cout << N << " " << M << "\n";
        for(int i=0; i<N; i++)
            cout << nums[i].num << "\n";
            //cout << "{" << nums[i].num << ", " << nums[i].isOdd << ", " << nums[i].mod << "}\n";

    }
    
    return 0;
}