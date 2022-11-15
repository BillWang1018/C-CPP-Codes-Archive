#include <stdio.h>
int main() {
    int a,b,c,A,B;
    scanf("%d %d", &a, &b);
    A = a, B = b;
    while(a%b) {
        c = a%b;
        a = b;
        b = c;
    }
    printf("%d", A*B/b);

}