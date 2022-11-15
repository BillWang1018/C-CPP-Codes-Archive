#include <iostream>
using namespace std;

void solve() {
    int ct[7], ans = 0;
    for(int i=1; i<7; i++)
        cin >> ct[i];
    //6
    ans += ct[6];
    ct[6]=0;
    //5
    ans += ct[5];
    ct[1]-=ct[5]*11;
    ct[5]=0;
    //4
    ans += ct[4];
    if(ct[4]*5 > ct[2]) {
        ct[1]-=(ct[4]*5-ct[2])*4;
        ct[2]=0;
    } else ct[2] -= ct[4]*5;
    ct[4]=0;
    //3 3->1,2->3,1->5
    ans += ct[3]/4 + ct[3]%4!=0;
    int tmp = ct[3]%4;
    if(tmp) {
        if(ct[2] <= 7-2*tmp) {
            ct[1] -= 36 - 9*tmp - 4*ct[2];
            ct[2]=0;
        } else 
            ct[2]-=7-2*tmp;
    }
    ct[3]=0;
    //2
    ans += ct[2]/9 + ct[2]%9!=0;
    tmp = ct[2]%9;
    if(tmp) {
        ct[1] -= 36 - 4*tmp;
    }
    //1
    if(ct[1]>0)
        ans += ct[1]/36 + (ct[1]%36!=0);
    
    cout << ans << "\n";
    return;
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}