#include <iostream>
using namespace std;


char keyboard[3][20] = {
    "qwertyuiop[]\\",
    "asdfghjkl;\'",
    "zxcvbnm,./"
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

    return 0;
}