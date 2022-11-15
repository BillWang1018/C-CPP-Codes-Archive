#include <iostream>
#include <vector>
#include <queue>
#define x first
#define y second
using namespace std;
int main() {
    int T, N, M;
    pair<int, int> cat;
    vector<string> board;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    cin >> T;
    while(T--) {
        cin >> N >> M;
        for(int i=0; i<N; i++) {
            board.push_back("");
            cin >> board[i];
            for(int j=0; j<M; j++) {
                if(board[i][j] == 'K') {
                    cat = {i, j};
                }
            }
        }

        queue<pair<int,int>> q;
        queue<int> dep;
        bool getM = false;

        q.push({cat.x, cat.y}), dep.push(0);
        while(!q.empty())  {
            pair<int, int> now = q.front();
            for(int i=0; i<4; i++) {
                if(board[now.x+dx[i]][now.y+dy[i]] == '@') {
                    cout << dep.front()+1 << "\n";
                    getM = true;
                    break;
                }
                if(board[now.x+dx[i]][now.y+dy[i]] == '.') {
                    q.push({now.x+dx[i], now.y+dy[i]});
                    dep.push(dep.front()+1);
                    board[now.x+dx[i]][now.y+dy[i]] = '#';
                }
            }
            if(getM) break;
            q.pop(), dep.pop();
        }
        if(!getM) cout << "= =\"\n";
    }
    return 0;
}