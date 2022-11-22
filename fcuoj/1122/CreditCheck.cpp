#include <iostream>
using namespace std;
int main() {
    int N, dig[4];
    cin >> N;
    while(N--) {
        for(int _{}; _<4; _++) {
            cin >> dig[_];
        }
        int dbdig[8], undbdig[8];
        for(int i{}; i<8; i++) {
            if(!(i%2)) {
                dbdig[i] = dig[i/2]/1000;
                undbdig[i] = (dig[i/2]%1000)/100;
            }
            else {
                dbdig[i] = (dig[i/2]%100)/10;
                undbdig[i] = (dig[i/2]%10);
            }
        }

        
        for(int i{}; i<8; i++) {
            dbdig[i] *= 2;
            while(dbdig[i]/10) {
                dbdig[i] = (dbdig[i]/10)+(dbdig[i]%10);
            }
        }
        int dbsum{}, undbsum{};
        for(int i{}; i<8; i++) {
            dbsum += dbdig[i];
            undbsum += undbdig[i];
        }

        cout << (!((dbsum+undbsum)%10) ? "Valid" : "Invalid") << "\n"; 
        
    }
    return 0;
}