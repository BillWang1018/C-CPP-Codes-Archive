#include <iostream>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	int N, Q, x, v;
	cin >> N;
	int num[N];
	bool check[N];
	for(int i=0; i<N; i++) {
		cin >> num[i];
		if(i==0) continue;
		check[i-1] = (num[i-1] <= num[i]);
	}
	cin >> Q;
	while (Q--) {
		cin >> x >> v;
		x--;
		num[x] = v;
		if(x!=0)
			check[x-1] = (num[x-1] <= num[x]);
		if(x!=N-1)
			check[x] = (num[x] <= num[x+1]);
		for(int i=0; i<N-1; i++) {
			if(!check[i]) {
				cout << "No\n";
				break;
			}
			if(i == N-2)
				cout << "Yes\n";
		}
		
	}
	return 0;
}
