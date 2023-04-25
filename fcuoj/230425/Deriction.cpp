#include <iostream>
using namespace std;
int main() {
    int k, n, m;
    while(1) {
        cin >> k;
        if(!k) break;
        cin >> n >> m;
        for(int i=0; i<k; i++) {
            int x, y;
            cin >> x >> y;
            if(x == n || y == m)
                cout << "divisa";
            if(x > n && y > m)
                cout << "NE";
            if(x < n && y > m)
                cout << "NO";
            if(x > n && y < m)
                cout << "SE";
            if(x < n && y < m)
                cout << "SO";
            cout << "\n";
        }
    }
    return 0;
}