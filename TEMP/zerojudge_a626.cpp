#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
int main() {
    int N{}, countPrint=1;
    cin >> N;

    if (N >= 2)
        cout << setw(10) << 2;
    if (N <= 2)
        return 0;
    
    vector<int> primes;
    primes.push_back(2);
    bool flag;
    int lastPrime = 2;
    for(int i=3; i<=N; i++) {
        flag = true;
        for(auto p:primes) {
            if(!(i%p)) {
                flag = false;
                break;
            }
        }
        if(!flag) continue; 
        for(int j = lastPrime; j<sqrt(i); j++) {
            if(!(i%j)) {
                flag = false;
                break;
            }
        }

        if(flag) {
            lastPrime = i;
            primes.push_back(i);
            cout << setw(10) << i;
            countPrint++;
            if(countPrint >= 5) {
                cout << '\n';
                countPrint = 0;
            }
        }
    }
    return 0;
}