#include <iostream>
#include <stack>
using namespace std;

struct POSITION {
	int x;
	int y;
} cell;

int main() {
	int T, R, C;
	cin >> T;
	while(T--) {
		POSITION joe, fire;
		cin >> R >> C;
		char maze[R][C];
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				
				cin >> maze[i][j];	
			}
		}
				
		
		
	}
	return 0;
}
