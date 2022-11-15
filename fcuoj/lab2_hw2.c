#include <stdio.h>
int main() {
    int n;
    while(scanf("%d", &n))
        printf(((!(n%4)&&(n%100))||!(n%400))?"YES!\n":"NOPE\n"); 
}