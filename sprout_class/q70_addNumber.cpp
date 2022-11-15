#include <iostream>
#include <queue>
using namespace std;

long long solve() {
    int N, n;
    cin >> N;
    priority_queue<long long, vector<long long>, greater<long long>> heap;
    for(int i=0; i<N; i++)
        cin >> n, heap.push(n);
    long sum = 0;
    while(true) {
        long long tmp = 0;
        tmp += heap.top();
        heap.pop();
        if(heap.empty()) break;
        tmp += heap.top();
        heap.pop();
        sum += tmp, heap.push(tmp);
    }
    return sum;
}
int main() {
    int T, N;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
    return 0;
}