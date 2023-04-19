#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct POSITION {
	int x;
	int y;
	int step;
};

POSITION interval[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // ^, >, v, <

int main() {
	int T, R, C;
	cin >> T;
	while(T--) {
		queue<POSITION> joe, fire;
		cin >> R >> C;
		vector<vector<char>> maze(R+2, vector<char>(C+2, '*'));

		//// DEBUG ////
		auto printMaze = [&]() {
			cout << "\n";
			for(int i=0; i<R+2; i++) {
				for(int j=0; j<C+2; j++) {
					cout << maze[i][j];
				}
				cout << "\n";
			}
		};
		//// DEBUG ////
		
		for(int i=1; i<=R; i++) {
			for(int j=1; j<=C; j++) {
				char c;
				cin >> c;	
				maze[i][j] = c;
				if(c == 'J') 
					joe.push({i,j,0});
				if(c == 'F')
					fire.push({i,j,0});
			}
		}

		int step = 0;
		bool isEscaped = false;
	
		while(!isEscaped) {
			
			// printMaze();

			if(joe.empty()) {  // RIP Joe hehe
				cout << "IMPOSSIBLE\n";
				break;
			}

			POSITION pos;
			int next_x, next_y;
			
			while(!fire.empty()) { // BFS Fire tile
				if(fire.front().step == step) {
					pos = fire.front();
					fire.pop();
					
					for(int _{}; _<4; _++) { 
						next_x = pos.x+interval[_].x;
						next_y = pos.y+interval[_].y;
						if(maze[next_x][next_y] != '#' && maze[next_x][next_y] != '*'
								&& maze[next_x][next_y] != 'F') {
							fire.push({next_x, next_y, step+1});
							maze[next_x][next_y] = 'F';	
						}
					}
				} else break;

			}

			while(!joe.empty() && !isEscaped) { // BFS Joe's possible move
				if(joe.front().step == step) {
					pos = joe.front();
					joe.pop();

					for(int _{}; _<4; _++) {
						next_x = pos.x+interval[_].x;
						next_y = pos.y+interval[_].y;
						if(maze[next_x][next_y] == '*') {
							isEscaped = true;
							cout << step+1 << "\n";
						}
						if(maze[next_x][next_y] == '.') {
							joe.push({next_x, next_y, step+1});
							maze[next_x][next_y] = 'J';
						}
					}
				} else break;
			}
			step++;
		}
	}
	return 0;
}
