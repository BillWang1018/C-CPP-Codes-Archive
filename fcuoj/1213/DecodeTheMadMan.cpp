#include <iostream>
using namespace std;


char keyboard[5][20] = {
    { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\' },
    { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'' },
    { 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/' }
};

pair<int,int> getKeyboardLocation(char c) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<20; j++) {
            if(!keyboard[i][j]) break;
            if(keyboard[i][j] == c) return {i,j};
        }
    }
    return {-1,-1};
}

int main() {
    int N;
    cin >> N;
    getchar();
    while(N--) {
        string str;
        pair<int,int> location;
        getline(cin, str);
        for(int i{}; i<str.size(); i++) {
            if(str[i] == ' ') {
                cout << " ";
                continue;
            }
            location = getKeyboardLocation(tolower(str[i]));
            cout << keyboard[location.first][location.second-2];
        }
        cout << "\n";
    }
    return 0;
}