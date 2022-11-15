#include <stdio.h>
int main() {
    int i;
    scanf("%d", &i);
    for (int j=i; j>=1; j--) {
        for (int k=j; k>=1; k--) {
            printf("*");
        }
        printf("\n");
    }
}