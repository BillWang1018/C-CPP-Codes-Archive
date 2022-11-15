#include <iostream>
using namespace std;
int main() {
	int N;
	cin >> N;
	string ans, guess;
	cin >> ans >> guess;
	int letter[200]={};
	bool check[100005]={};
	for(int i=0; i<N; i++) {
		if(guess[i] == ans[i]) {
			check[i]=true;
		} else {
			letter[ans[i]]++;
		} 
	}
	for(int i=0; i<N; i++) {
		if (check[i]) {
			cout << "M";	
		} else if (letter[guess[i]] > 0) {
			letter[guess[i]]--;
			cout << "P";
		} else {
			cout << "N";
		}
	}
	cout << "\n";
	return 0;
}
