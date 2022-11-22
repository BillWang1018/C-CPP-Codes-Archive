#include <iostream>
using namespace std;
int main() {
    int a,b,c,d;
    while(true) {
        int deg{};
        cin >> a >> b >> c >> d;
        if(a+b+c+d == 0) break;
        int tmp;
        //step1
        deg += 360*2;
        //step2
        tmp = a-b;
        deg += ((tmp < 0)?tmp+40:tmp)*9;
        //step3
        deg += 360;
        //step4
        tmp = c-b;
        deg += ((tmp < 0)?tmp+40:tmp)*9;
        //step5
        tmp = c-d;
        deg += ((tmp < 0)?tmp+40:tmp)*9;


        cout << deg << "\n";
    }
    return 0;
}