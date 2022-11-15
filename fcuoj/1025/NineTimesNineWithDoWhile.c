#include <stdio.h>
int main() {
    int x=7, y=9, i, j;
    i=j=1;
    do {
        j=1;
        do printf("%d*%d=%d%c", i, j++, i*j, ((j==7) ? '\n' : ' '));
        while(j <= 7);
        i++;
    } while(i <= 9);
}