#include <stdio.h>
int main() {
    int n,p=1;
    scanf("%d", &n);
    
    for(int i=2; i<=n; i++)
        p*=i;
    printf("%d", p);
}