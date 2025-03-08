#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Term;

void foo(Term *t) {
    t[1].a = 2;
    t[1].b = 22;
}

int main() {
    int c1,c2;
    scanf("%d%d%*c", &c1, &c2);
    scanf("%d%d%*c", &c1, &c2);

    printf("%d %d\n", c1, c2);
}