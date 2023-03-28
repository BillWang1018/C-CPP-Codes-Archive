#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    int T, l;
    cin >> T;
    while(T--) {
        vector<int> prices;
        
        while(cin >> l) {
            if(!l) break;
            prices.push_back(l);
        }
        sort(prices.begin(), prices.end(), 
            [](int a, int b) {
                return (a > b);
            }
        );

        int total{}, valid=1;
        for(int t=1; t <= prices.size(); t++) {
            total += round(pow(prices[t-1], t));
            if(total > 2.5e5) {
                valid=0;
                break;
            }
        }
        cout << ((valid)? to_string(2*total): "Too expensive") << "\n";

    }
    return 0;
}