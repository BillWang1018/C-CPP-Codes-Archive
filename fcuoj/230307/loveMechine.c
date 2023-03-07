#include <stdio.h>

int sizeofstr(char* str) {
    int i=0;
    while(1) {
        i++;
        if(str[i] == '\0')
        return i;
    }
}

int binToDec(char* bin) {
    int size = sizeofstr(bin);
    int res = 0;
    for(int i=0; i<size; i++) {
        if(bin[i] == '1')
            res += (1 << size-i-1);
    }
    return res;
}

int gcd(int a, int b) {
    if(b<=1)
        return 1;
    a = a%b;
    if(a != 0) 
        b = gcd(b, a);
    return b;
}

int main() {
    int n, size, dec1, dec2;
    char bin[35];
    scanf("%d", &n);
    for(int i=1; i<=n; i++) {
        dec1 = dec2 = 0;
        scanf("%s", bin);
        dec1 = binToDec(bin);
        scanf("%s", bin);
        dec2 = binToDec(bin);

        printf("Pair #%d: ", i);
        if(gcd(dec1, dec2) > 1) {
            printf("All you need is love!\n");
        } else {
            printf("Love is not all you need!\n");
        }
    }

    return 0;
}