#include <iostream>
using namespace std;
bool check(int *a, int N) {
	for(int i=0; i<N-1; i++) {
		if(a[i] > a[i+1]) return false;
	}
	return true;
}
int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	int N, Q, x, v;
	cin >> N;
	int num[N];
	for(int i=0; i<N; i++) {
		cin >> num[i];
	}
	cin >> Q;
	while (Q--) {
		cin >> x >> v;
		x--;
		num[x] = v;
		if(check(num, N)) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
