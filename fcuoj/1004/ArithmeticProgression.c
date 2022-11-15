#include <stdio.h>
int main() {
    int a,b,d,sum;
    sum=0;
    scanf("%d %d %d", &a, &b, &d);
    for(int i=a; i<=b; i+=d) {
        printf("%d\n", i);
        sum += i;
    }
    printf("%d", sum);
}