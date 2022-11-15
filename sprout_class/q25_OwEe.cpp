#include<iostream>
#include<queue>
using namespace std;
int main() {
    int N, M;
    string cmd;
    cin >> N >> M;
    for(int i = 0; i<M; i++) {
        cin >> cmd;
        if(cmd == "ADD") {
            int a, b;
            cin >> a >> b;
        } else if(cmd == "LEAVE") {
            int a;
            cin >> a;
        } else {
            int a, b;
            cin >> a >> b;
        }
    }

    return 0;
}