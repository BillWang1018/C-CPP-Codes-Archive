#include <iostream>
using namespace std;
bool check(int *a, int N) {
	for(int i=0; i<N; i++) {
		cout << a[i];
	}
	cout << "\n";
	for(int i=0; i<N-1; i++) {
		if(a[i] > a[i+1]) return false;
	}
	return true;
}
int main() {
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
