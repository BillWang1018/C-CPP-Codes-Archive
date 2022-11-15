#include <iostream>
#include <vector>
using namespace std;
int main() {
    int T, N, M;
    cin >> T;
    while(T--) {
        cin >> N >> M;
        vector<int> fu(N), sa(N);
        vector<vector<int>> dp(N, vector<int>(M));
        for(int i=0; i<N; i++) {
            cin >> fu[i] >> sa[i];
            
        }
    }
    return 0;
}