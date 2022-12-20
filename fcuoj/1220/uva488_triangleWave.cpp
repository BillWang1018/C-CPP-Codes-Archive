#include <iostream>
#include <fstream>
using namespace std;
int main() {
    int N;
    cin >> N;
    while(N--) {
        int amp, freq;
        cin >> amp >> freq;
        for(int f{}; f<freq; f++) {
            if(f) cout << "\n";
            for(int a=1; a<amp; a++) {
                for(int i{}; i<a; i++) {
                    cout << a;
                }
                cout << "\n";
            }
            for(int a=amp; a>0; a--) {
                for(int i{}; i<a; i++) {
                    cout << a;
                }
                cout << "\n";
            }
        }
        cout << "\n";

    }
    return 0;
}