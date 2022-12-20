#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int N, caseCount{};
    string str;
    while(cin >> N) {
        int cool{};
        while(N--) {
            cin >> str;
            if(str.size() <= 2) continue;
            vector<int> count(130);
            for(int i{}; i<str.size(); i++) {
                count[str[i]]++;
            }
            
            sort(count.begin(), count.end());
            if(!count[count.size()-2]) continue;

            for(int i{}; i<count.size(); i++) {
                if(!count[i]) continue;
                if(count[i] == count[i-1]) {
                    break;
                }
                if(i == count.size()-1)
                    cool++;
            }

        }
        cout << "Case " <<  ++caseCount << ": " << cool << "\n";

    }

    return 0;
}