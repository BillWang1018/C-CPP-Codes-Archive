#include <iostream>
using namespace std;
int main() {
    int N;
    int top = 1, tmp;
    string str;
    string dirc[] = {"east","west","south","north"};
    int next[] = {3,4,2,5};

    cin >> N;
    while(N--) {
        cin >> str;
        for(int i=0; i<4; i++) {
            if(str == dirc[i]) {
                tmp = top;
                top = next[i];
                next[(i/2)*2 + ((i/2)*2 == i)] = tmp;
                next[(i/2)*2 + ((i/2)*2 != i)] = 7-tmp;

                break;
            }
        }

    }
    cout << top;
    return 0;
}