#include <stdio.h>
int main() {
    double n, dsum=0;
    int count, isum=0;
    for(int i=0; i<5; i++) {
        scanf("%lf", &n);
        dsum += n;
    }
    scanf("%d", &count);
    for(int i=count; i>0; i--) {
        isum += i;
    }
    printf("%.2f\n%d", dsum/5, isum);
    return 0;
}