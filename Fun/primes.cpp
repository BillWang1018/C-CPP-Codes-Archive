#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> primes;
    primes.push_back(2);
    for(int i=3; i<=200; i+=2) {
        bool flag = true;
        for(int prime : primes) {
            if(!(i%prime)) {
                flag = false;
                break;
            }
        }
        if(flag) {
            primes.push_back(i);
        }
    }

    int count{};

    cout << "========== Primes from 100 and less than 200 ==========\n";
    for(int prime : primes) {
        if(prime < 100) continue;
        count++;
        cout << prime << " ";
    }
    cout << "==========> element counter: " << count << "\n\n";
    count=0;


    cout << "========== p*q from 100 and less than 200 ==========\n\n";
    cout << "p \\q ";
    for(int p : primes) {
        if(p < 100) continue;
        cout << "-" << p << "- ";
    }
    cout << '\n';
    for(int p1 : primes) {
        if(p1 < 100) continue;
        cout << p1 << "| ";
        for(int p2 : primes) {
            if(p2 < 100) continue;
            count++;
            cout << p1 * p2 << " ";
        }
        cout << '\n';
    }
    cout << "==========> element counter: " << count << '\n';

    return 0;
}