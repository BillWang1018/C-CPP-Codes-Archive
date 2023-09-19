#include <stdio.h>
void add() {
    int a[9], b[9], n;
    for(int i=0; i<9; i++) {
        scanf("%d", &n);
        a[i] = n;
    }
    for(int i=0; i<9; i++) {
        scanf("%d", &n);
        b[i] = n;
    }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            printf("%d ", a[i*3+j]+b[i*3+j]);
        }
        printf("\n");
    }
}
void cross() {
    int a[9], b[9], n;
    for(int i=0; i<6; i++) {
        scanf("%d", &n);
        a[i] = n;
    }
    for(int i=0; i<4; i++) {
        scanf("%d", &n);
        b[i] = n;
    }

    for(int i=0; i<3; i++) {
        for(int j=0; j<2; j++) {
            int sum=0;
            for(int k=0; k<2; k++) {
                sum += a[i*2+k]*b[k*2+j];
            }
            printf("%d ", sum);
        }
        printf("\n");
    }
}
int main() {
    
    add(), cross();
    
    return 0;
}