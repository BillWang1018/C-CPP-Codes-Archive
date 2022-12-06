#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char, int> note ({{'c', 0b0111001111}, {'d', 0b0111001110}, {'e', 0b0111001100}, {'f', 0b0111001000}, {'g', 0b0111000000}, {'a', 0b0110000000}, {'b', 0b0100000000},
        {'C', 0b0010000000}, {'D', 0b1111001110}, {'E', 0b1111001100}, {'F', 0b1111001000}, {'G', 0b1111000000}, {'A', 0b1110000000}, {'B', 0b1100000000}});

int main() {
    int t;
    cin >> t;
    getchar();
    while(t--) {
        int prev{}, now{}, count[10]{};
        string notes;
        getline(cin, notes);
        for(char n : notes) {
            now = note[n];
            for(int i=0; i<10; i++) {
                count[i] += (((1<<i & prev) ^ (1<<i & now)) && (1<<i & now));
            }
            prev = now;
        }

        for(int i=9; i>=0; i--) {
            cout << count[i] << (i ? " " : "");
        }
        cout << "\n";

    }
    return 0;
}