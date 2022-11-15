#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<bool> v[1005];
int lx[] = {0, 1, 0, -1};
int ly[] = {-1, 0, 1, 0};

// void printv(int h, int w) {
//     cout << "----------\n";
//     for(int i=0; i<=h; i++) {
//         for(int j=0; j<=w; j++) {
//             if(v[i][j]) cout << "#";
//             else cout << ".";
//         }
//         cout << "\n";
//     }
// }

int main() {
    int t, h, w;
    string s;
    cin >> t;
    while(t--) {
        cin >> h >> w;
        for(int i=0; i<=h+1; i++) {
            if(i==0 || i==h+1) {
                v[i] = vector<bool>(w+2, true);
                continue;
            } else {
                v[i] = vector<bool>(w+2, false);
                v[i][0] = v[i][w+1] = true;
            }
            cin >> s;
            for(int j=0; j<w; j++) {
                if(s[j]=='#') v[i][j+1] = true;
            }
        }
        int count = 0;
        int x,y;
        queue<int> qx, qy; 

        for(int i=1; i<=h; i++) {
            for(int j=1; j<=w; j++) {
                if(!v[i][j]) {
                    count++;
                    v[i][j] = true;
                    qx.push(i), qy.push(j);
                    while(!qx.empty()) {
                        x = qx.front(), y = qy.front();
                        qx.pop(), qy.pop();
                        for(int l=0; l<4; l++) {
                            if(!v[x+lx[l]][y+ly[l]]) {
                                v[x+lx[l]][y+ly[l]] = true;
                                qx.push(x+lx[l]);
                                qy.push(y+ly[l]);
                            }
                        }
                    }
                }
            }
        }

        cout << count << '\n';

    }
    return 0;
}