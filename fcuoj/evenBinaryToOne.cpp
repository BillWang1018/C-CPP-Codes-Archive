#include <stdio.h>
//using namespace std;
int main() {
    int funNum = 0xff;
    for (int i=2; i<=0xff; i<<=2) 
        funNum &= (0xff-i);
    printf("%x", funNum);
    //cout << funNum;
    return 0;
}