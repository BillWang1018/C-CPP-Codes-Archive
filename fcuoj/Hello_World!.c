#include <stdio.h>
#include <math.h>

int main() {
    int i, a, c=0, n;
    while(1) {
        c++;
        scanf("%d", &a);
        if(a<0) break;
        for(i=0, n=1; n<a; i++) {
            n*=2;
        }
        printf("Case %d: %d\n", c, i);
    }
}