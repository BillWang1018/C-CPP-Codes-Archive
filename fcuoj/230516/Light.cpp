#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int T, M, N;
    cin >> T;
    while(T--) {
        int row[1005], col[1005], light[1005]{}, ans{};
        cin >> M >> N;
        for(int _{}; _<M; _++)
            cin >> row[_];
        for(int _{}; _<N; _++) 
            cin >> col[_];
        
        sort(row, row+M, greater<int>());
        sort(col, col+N, greater<int>());
        
        for(int r{}; r<M; r++) {
            ans += row[r];
            for(int i=0; i<row[r]; i++)
                light[i]++;
        }

        for(int c{}; c<N; c++) {
            if(col[c] > light[c])
                ans += (col[c] - light[c]);
        }

        cout << ans << "\n";

    }
    return 0;
}