#include <stdio.h>
int main() {
    int amount;
    do {
        scanf("%d", &amount);
    } while(amount > 1000 || amount < 0);

    printf("%d %d %d", amount/100, (amount%100)/10, amount%10);

    return 0;
}