#include <stdio.h>
#include <string.h>
int main() {
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    for(int i=0; i<len/2; i++) {
        if(s[i] != s[len-i-1]) {
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}