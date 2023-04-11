#include <iostream>
#include <vector>
typedef long long int ll;
using namespace std;
int main() {
	int T, n;
	ll elem;
	string s;
	cin >> T;
	for(int t=1; t<=T; t++) {
		
		cin >> s >> s >> n;
		vector<ll> mtx;
		for(int i=0; i<n*n; i++) {
			cin >> elem;
			mtx.push_back(elem);
		}
		
		bool flag = 1;
		int index;
		for(int i=0; i<=n*n/2; i++) {
			if((mtx[i] != mtx[n*n-1-i]) || (mtx[i]<0) || (mtx[n*n-1-i]<0)) {
				flag = 0;
				break;
			}
			
		}
		cout << "Test #" << t << ": " 
			<< (flag? "Symmetric" : "Non-symmetric")
			<< ".\n";
		
	}
	
	return 0;
}
