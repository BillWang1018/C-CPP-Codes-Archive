#include <stdio.h>
int main() {
    int a,b;
    scanf("%d %d", &a, &b);
    for(int i=1; i<=a; i++) {
        for(int j=1; j<=b; j++) {
            if(j!=b)
                printf("%d*%d=%d ", i, j, i*j);
            else
                printf("%d*%d=%d    ", i, j, i*j);
        }
        if(i!=a) printf("\n");
    }