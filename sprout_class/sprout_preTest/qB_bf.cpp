#include <iostream>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	long long int T, N, X;
	cin >> T;
	while(T--) {
		cin >> N >> X;
		int a[N]={};
		for(int i=0; i<N; i++) {
			cin >> a[i];
		}
		bool flag = true;
		for(int i=2; i<=N && flag; i++) {//length of sub-seq
			for(int j=0; j+i<=N && flag; j++) {//begin index
				long long int sum=0;
				for(int k=j; k<j+i; k++) {
					sum += a[k];
				}
				if(sum < X*i) {
					flag = false;
				}
			}
		}
		if(flag) cout << "Yes\n";
		else cout << "No\n";
	}
	
	return 0;
}
