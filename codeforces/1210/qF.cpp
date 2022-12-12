#include <iostream>
#include <vector>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int m;
        long long int ans{};
        bool flag = true;
        cin >> m;
        vector<int> tree(m);
        for(int i=0; i<m; i++) {
            cin >> tree[i];
        }
        for(int i=1; (m/i)>=1; i<<=1) { //range of segment
            for(int j=0; j<m; j+=i) {  
                if(tree[j] > tree[(j+i/2)]) {
                    if( abs(tree[j] - tree[(j+i/2)]) != i/2) {
                        flag = false;
                        goto printAns; //can't form perfect tree, skip all check
                    } else {
                        ans++;
                        for(int k=j; k<j+(i/2); k++) {
                            swap(tree[k], tree[k+(i/2)]);
                        }
                    }
                    /*/ 
                    for(int _{}; _<m; _++) {
                        cout << tree[_] << " ";
                    }
                    cout << endl;
                    /*/ 
                }
            }
        }

        printAns:

        if (flag) {
            cout << ans << "\n";
        } else {
            cout << -1 << "\n";
        }

    }
    return 0;
}