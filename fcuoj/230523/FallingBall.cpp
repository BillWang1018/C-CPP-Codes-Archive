#include <iostream>
using namespace std;
int main() {
    int N, D, I;
    cin >> N;
    while(N--) {
        cin >> D >> I;
        bool tree[(1<<D)]{};
        for(int i{}; i<I; i++) {
            int num{};
            for(int d{}; d<D; d++) {
                if(d+1 == D && i+1 == I) {
                    cout << num+1 << "\n";
                    break;
                }
                if(tree[num]) {
                    tree[num] = !tree[num];
                    num = num*2 + 2;
                } else {
                    tree[num] = !tree[num];
                    num = num*2 + 1;
                }
            }
        }
    }

    cin >> N;
    return 0;
}