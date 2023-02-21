#include <stdio.h>

void reverse(int *num, int len) {
    int *l = num, *r = num+len-1, tmp;
    while(l < r) { // cool bitwise xor thing to swap(l,r)
        *l ^= *r;
        *r ^= *l;
        *l ^= *r;
        
        l++;
        r--;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int num[n];
    for(int i=0; i<n; i++) {
        scanf("%d", num+i);
    }
    reverse(num, n);
    for(int i=0; i<n; i++) {
        printf("%d ", *(num+i));
    }

}