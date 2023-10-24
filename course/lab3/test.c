#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    int i, *pi, **ppi;
    i=10;
    pi = &i;
    ppi = &pi;

    printf("%d\n", i);
    *pi = 1;
    printf("%d\n", i);
    **ppi = 2;
    printf("%d\n", i);
    

}