#include <iostream>
#include <queue>
using namespace std;
int main() {
	string s, subs;
	while(getline(cin, s)) {
		queue<int> space;
		for(int i=0; i<s.size(); i++) {
			if(s[i] == ' ') space.push(i);
		}
		space.push(s.size());
		
		int hold = 0, next = space.front();
		space.pop();
		while(!space.empty()) {
			for(int i=next-1; i>=hold; i--)
				cout << s[i];
			
			hold = next+1, next = space.front();
			space.pop();
			cout << " ";
		}
		for(int i=next-1; i>=hold; i--)
			cout << s[i];
		cout << "\n";
	}
	
	return 0;
}
