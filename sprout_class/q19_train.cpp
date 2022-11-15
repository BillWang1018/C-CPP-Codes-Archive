#include <iostream>
#include <stack>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, b, n=1;
        bool flag = true;
        stack<int> sta;
        cin >> N;
        for(int i=1; i<=N; i++) {
            cin >> b;

            if(!flag) // Failed
                continue;
            
            if(sta.empty()) sta.push(n++);

            while(sta.top() != b) { // Not the car we need
                if(n>N) { // Failed (no more in staA)
                    flag = false;
                    break;
                } else
                    sta.push(n++);
            }
            if(flag)
                sta.pop();
        }
        cout << (flag ? "Yes" : "No");
        cout << "\n";
    }

    return 0;
}