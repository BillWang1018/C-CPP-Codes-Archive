#include <stdio.h>
int main() {
    int n;
    while(scanf("%d", &n)!=EOF) {
        int sum, empty, complement;
        sum = empty = n;
        complement = 0;
        while(1) {
            if(!complement)
                if(empty % 3) {
                    complement = 3-(empty%3);
                    empty += complement;
                }
            if(((empty/3)+(empty%3) < complement) || empty<3) break;
            sum += (empty/3);
            empty = (empty/3)+(empty%3);
        }
        printf("%d\n", sum);
    }
}