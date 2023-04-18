#include <iostream>
using namespace std;
int main() {
	string kb = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";	
	string input;
	while(getline(cin, input)) {
		for(int i=0; i<input.size(); i++) {
			if(input[i] == ' ') cout << ' ';
			for(int j=0; j<kb.size(); j++) {
				if(input[i] == kb[j]) cout << kb[j-1];
			}
		}
		cout << "\n";
	}
	
	return 0;
}
