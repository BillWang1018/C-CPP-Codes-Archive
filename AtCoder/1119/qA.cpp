#include <iostream>
#include <vector>
using namespace std;
int main() {
    int N, K, A;
    cin >> N >> K;
    vector<int> num(N);
    for (int i=0; i<N; i++) {
        cin >> A;
        num[i] = A;
    }
    for (int i=0; i<N; i++) {
        cout << ((i+K < N) ? num[i+K] : 0) << " ";
    }
    return 0;
}