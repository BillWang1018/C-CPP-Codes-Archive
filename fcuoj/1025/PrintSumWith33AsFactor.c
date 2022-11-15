#include <stdio.h>
int main() {
    int n;
    int sum=0;
    scanf("%d", &n);
    for(int i=100; i<=n; i++) {
        sum += (i%33) ? 0 : i;
    }
    printf("%d", sum);
}