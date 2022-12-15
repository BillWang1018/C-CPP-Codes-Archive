#include <iostream> // cin, cout
#include <vector>   // vector<int>
#include <iomanip>  // setw()
#include <cmath>    // sqrt()
using namespace std;

//function to print number with (10) width
void printWithWidth(int i) {
    cout << setw(10) << i;
}

int main() {
    int N, countPrint;
    bool flag;
    vector<int> primes;
    primes.push_back(2);
    primes.push_back(3);
    int lastPrime = 3;

    // find every prime within (1000) and add it to vector (primes)
    for(int i=5; i<=1000; i++) {
        flag = true; // flag maintains (true) if the number is prime
        for(auto p:primes) { // iterate through known (primes) using for-each loop
            if(!(i%p)) { // test if (i) isn't prime
                flag = false;
                break;
            }
        }
        if(!flag) continue; // continue if (i) isn't prime
        for(int j = lastPrime; j<sqrt(i); j+=2) { // check possible factors from last prime found
            if(!(i%j)) {
                flag = false;
                break;
            }
        }

        if(flag) { // if (i) is prime, add it to (primes), and sync (lastPrime)
            lastPrime = i;
            primes.push_back(i);
        }

    }

    while(cin >> N) {
        countPrint = 0;
        for (auto i : primes) {
            if(i > N) break; // print (i) until (N)
            printWithWidth(i);
            countPrint++;
            if(countPrint >= 5) { // endl if 5 numbers in a row
                cout << '\n';
                countPrint = 0;
            }
        }
        cout << '\n';
    }
    return 0;
}