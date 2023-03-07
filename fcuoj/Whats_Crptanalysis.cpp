#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

bool pair_comp(pair<int,char> p1, pair<int,char> p2) {
	if(p1.first != p2.first) return p1.first > p2.first;
	return p1.second < p2.second;
}

int main() {
	int n;
	cin >> n;
	cin.get();
	int count[200] = {};
	for(int i=0; i<n; i++) {
		string str; 
		getline(cin, str);
		for(int j=0; j<str.size(); j++) {
			str[j] = toupper(str[j]);
			if(str[j] >= 'A' && str[j] <= 'Z') {
				count[str[j]]++;
			}
		}
	}	
	vector<pair<int,char>> v;
	for(int i=0; i<26; i++) {
		v.push_back({count['A'+i], 'A'+i});
	}
	sort(v.begin(), v.end(), pair_comp);
	for(int i=0; i<26; i++) {
		if(v[i].first == 0) break;
		cout << v[i].second << " " << v[i].first << "\n";
	}
	
	return 0;
}
