#include <iostream>
#include <cmath>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	int N, M, C, l, r, a;
	cin >> N >> M >> C;
	long long int sum[M]={};
	int cost[M]={};
	
	for(int i=0; i<N-1; i++) {
		cin >> l >> r >> a;
		l--, r--;
		for(int j=l; j<=r; j++) {
			sum[j] += a;
		}
	}
	for(int i=0; i<M; i++) {
		cin >> cost[i];
	}
	int minc=999999, maxv=0;
	for(int i=0; i<M; i++) {
		if(maxv < sum[i]) {
			maxv = sum[i];
			minc = cost[i];
		}
	}
	for(int i=0; i<M; i++) {
		if(sum[i]+C >= maxv) {
			minc = min(minc, cost[i]);
		}
	}
	cout << minc << "\n";
	return 0;
}
