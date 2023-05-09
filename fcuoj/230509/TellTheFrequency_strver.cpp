#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct st {
    char ch;
    int count;
};

int main() {
    string str;
    bool flag = 0;
    int count[1000]{};
    while(getline(cin, str)) {
        for(int i{}; i<str.size() && str[i]!='\n'; i++) {
            if(str[i] == 26) return 0;
            count[str[i]]++;
        }

        st ans[255]{};
        int j{};
        for(int i=255; i>=0; i--)
            if(count[i])
                ans[j++] = {(char)i, count[i]};

        sort(ans, ans+j, [](st a, st b) {
            return (a.count < b.count) ? true : (a.ch > b.ch);
        });

        for(int i{}; i<j; i++)
            cout << (int)ans[i].ch << " " << ans[i].count << "\n";
        cout << "\n";
        memset(count, 0, 1000);
    }

    return 0;
}