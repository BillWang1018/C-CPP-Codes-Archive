#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct st {
    char ch;
    int count;
};

int main() {
    char c;
    bool flag = 0;
    int count[1000]{};
    while(1) {
        c = getchar();
        if(c == EOF) break;
        if(flag) flag = 0, cout << "\n";
        if(c == '\n') {
            flag = 1;
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
            
            memset(count, 0, 1000);
        } else
            count[c]++;
    }

    return 0;
}