#include <stdio.h>
int main() {
    int count[200]={}, sum=0;
    char c;
    while(1) {
        scanf("%c", &c);
        if(c == 'Z') break;
        if(c == ' ') continue;
        count[c]++;
        sum++;
    }
    for(int i=0; i<6; i++) {
        char ch = 'A'+i;
        printf("%c:%d ", ch, count[ch]);
    }
    printf("sum:%d", sum);
}