#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int S, caseCount{};
    int sumOfFactors[1005]{};
    for(int i{}; i<1005; i++) {
        for(int j=1; j<=sqrt(i); j++) {
            if(!(i%j)) sumOfFactors[i] += (j+i/j);
            if(i == j*j) sumOfFactors[i] -= j;
        }
        // cout << sumOfFactors[101] << " ";
    }

    

    while(1) {
        caseCount++;
        cin >> S;
        if(!S) break;
        for(int i=S; i>=1; i--) {
            if(sumOfFactors[i] == S) {
                cout << "Case " << caseCount << ": " << i << "\n";
                break;
            }
            if(i == 1)
                cout << "Case " << caseCount << ": " << -1 << "\n";
        }
    }
    return 0;
}