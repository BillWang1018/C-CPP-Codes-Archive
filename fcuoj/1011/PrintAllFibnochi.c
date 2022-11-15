#include <stdio.h>
int main() {
    int fib[100] = {0,1,1};
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        if(i>2)
            fib[i] = fib[i-1] + fib[i-2];
        printf("%d\n", fib[i]);
    }
}