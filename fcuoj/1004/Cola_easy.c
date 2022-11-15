#include <stdio.h>
int main() {
    int n, sum;
    scanf("%d", &n);
    sum = n;
    while(n>=3) {
        sum += n/3;
        n = (n/3)+(n%3);
    }
    printf("%d", sum);
}