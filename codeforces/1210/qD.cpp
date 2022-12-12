#include <iostream>
#include <vector>
using namespace std;
int main() {
    int N;
    cin >> N;
    while(N--) {
        int L, sum{};
        cin >> L;
        vector<int> qu(L);
        for(int i{}; i<L; i++) {
            cin >> qu[i];
        }

        for(int i{}; i<L; i++) {
            for(int j=i; j<L; j++) {
                if(qu[i] > qu[j]) {
                    sum++;
                    swap(qu[i], qu[j]);
                }
            }
        }
        cout << sum << "\n";
    }
    return 0;
}