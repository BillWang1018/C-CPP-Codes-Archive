#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0),cin.tie(0);
	int N,B,a;
	cin >> N;
	B = N/2;
	vector<int> team, ppl;
	for(int i=0; i<N; i++) {
		cin >> a;
		ppl.push_back(a);
	}
	sort(ppl.begin(), ppl.end());
	for(int i=0; i<B; i++) {
		team.push_back(ppl[i] + ppl[N-i-1]);
	}
	//calc ans
	long long int ans=0;
	for(int i=0; i<B-1; i++){
		for(int j=i+1; j<B; j++) {
			ans += abs(team[i]-team[j]);
		}
	}
	cout << ans << "\n";
	return 0;
}
