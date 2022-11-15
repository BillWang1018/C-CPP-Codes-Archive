#include <iostream>
using namespace std;
int main() {
    int N;
    cin >> N;
    cout << "Lumberjacks:\n";
    while(N--) {
        int grp[10];
        bool result = true;
        for(int i=0; i<10; i++) {
            cin >> grp[i];
        }
        bool greater = (grp[0] < grp[1]);
        for(int i=1; i<9; i++) {
            if(greater && (grp[i] < grp[i+1]))
                continue;
                
            if((!greater) && (grp[i] > grp[i+1]))
                continue;
            
            result = false;
            break;
        }

        cout << (result ? "Ordered" : "Unordered") << "\n";
    }
    return 0;
}