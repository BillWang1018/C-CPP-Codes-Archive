#include <iostream>
using namespace std;
int main() {
	int mtx1[9], mtx2[9];
	for(int i=0; i<9; i++) {
		cin >> *(mtx1+i);
	}
	for(int i=0; i<9; i++) {
		cin >> *(mtx2+i);
	}
	
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			int sum{};
			for(int k=0; k<3; k++) {
				sum += *(mtx1+(i*3+k)) * *(mtx2+(k*3+j));
			}
			cout << sum << (j==2 ? "" : " ");
		}
		cout << (i==2 ? "" : "\n");
	}
	
	return 0;
}
