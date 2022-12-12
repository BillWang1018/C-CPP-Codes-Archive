#include <iostream>
#include <vector>
using namespace std;
int main() {
    int t;
    cin >> t;
    getchar();
    while(t--) {
        int n, m;
        cin >> n >> m;
        getchar();
        vector< string > box(n), result(n, string(m, '.'));
        for(int i{}; i<n; i++) {
            getline(cin, box[i]);
            //getchar();
        }
//
        for(int j{}; j<m; j++) {
            int count{};
            for(int i{}; i<n; i++) {
                if(box[i][j] == '*') {
                    count++;
                }
                if(box[i][j] == 'o') {
                    result[i][j] = 'o';
                    for(int k=i-1; count>0; k--, count--) {
                        result[k][j] = '*';
                    }
                }
                if(i == n-1) {
                    for(int k=i; count>0; k--, count--) {
                        result[k][j] = '*';
                    }
                }
                
            }
        }
//
        for(int i{}; i<n; i++) {
            for(int j{}; j<m; j++) {
                cout << result[i][j];
            }
            cout << "\n";
        }
//
    }
    return 0;
}