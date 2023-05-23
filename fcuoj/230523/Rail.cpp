#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int main() {
    int N, tmp;
    while(cin >> N) {
        if(!N) break;
        while(1) {
            cin >> tmp;
            if(!tmp) break;

            stack<int> s;
            vector<int> dirA(N), dirB(N);

            dirB[0] = tmp;
            for(int i=1; i<N; i++) {
                cin >> tmp;
                dirB[i] = tmp;
            }

            for(int i{}; i<N; i++) {
                dirA[i] = i+1;
            }

            auto carA = dirA.begin(), carB = dirB.begin();
            
            while(carB != dirB.end()) { // if all cars are passed
                // cout << *carB << " | " << (s.empty() ? -1 : s.top()) << " | " << *carA << "\n";
                if (s.empty() || *carB != s.top()) { // if stack.top is not desired
                    if (carA != dirA.end()) // if there's car in dirA
                        s.push(*carA++);
                    else // if there's no car in dirA
                        break;
                } else { // if stack.top is desired
                    s.pop();
                    carB++;
                }
            }

            cout << (carB == dirB.end() ? "Yes" : "No") << "\n";
            
        }
        cout << "\n";
    }
    return 0;
}