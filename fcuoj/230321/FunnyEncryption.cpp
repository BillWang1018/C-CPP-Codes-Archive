#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string changeBase(long long num, int org) {
    long long newNum{};
    int i=0;
    while(num) {
        newNum += ((num%10) * round(pow(org, i++)));
        num /= 10;
    }
    string bin{};
    while(newNum) {
        bin = (char)(newNum%2+'0') + bin;
        newNum /= 2;
    }
    return bin;
}

int countone(string str) {
    int ans{};
    for(char c:str)
        if(c == '1') ans++;

    return ans;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        long long N;
        cin >> N;
        string x1 = changeBase(N, 10);
        string x2 = changeBase(N, 16);

        cout << countone(x1) << " " << countone(x2) << "\n";
    }
    return 0;
}