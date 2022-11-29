#include <iostream>
using namespace std;
int main() {
    int N;
    string str;
    getline(cin, str);
    N = atoi(str.c_str());
    for(int _{}; _<N; _++) {
        cout << "Case " << _+1 << ": ";
        getline(cin, str);
        for(int i{}; i<(str.size());) {
            char ch;
            int num, flag;
            ch = str[i++];
            flag = i;
            while(str[flag] >= '0' && str[flag] <= '9')
                flag++;
            num = atoi(str.substr(i, flag-i+1).c_str());   
            for(int j{}; j<num; j++)
                cout << ch;
            i = flag;
        }
        cout << "\n";
    }
    return 0;
}