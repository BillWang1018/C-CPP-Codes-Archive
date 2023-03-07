#include <stdio.h>
#include <stdlib.h>
int main() {
    // initialize arrays
    int **mat1, **mat2, **ans;
    mat1 = (int**) malloc( sizeof(int*) * 3);
    mat2 = (int**) malloc( sizeof(int*) * 3);
    ans = (int**) malloc( sizeof(int*) * 3);
    for(int i=0; i<3; i++) {
        *(mat1+i) = (int*) malloc( sizeof(int) * 3 );
        *(mat2+i) = (int*) malloc( sizeof(int) * 3 );
        *(ans+i) = (int*) malloc( sizeof(int) * 3 );
    }

    // input
    for(int i=0; i<3; i++) 
        for(int j=0; j<3; j++) 
            scanf("%d", (*(mat1+i)+j));
    for(int i=0; i<3; i++) 
        for(int j=0; j<3; j++) 
            scanf("%d", (*(mat2+i)+j));
    
    //perform operations
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            int add=0;
            for(int k=0; k<3; k++) {
                add += (*(*(mat1+i)+k)) * (*(*(mat2+k)+j));
            }
            *(*(ans+i)+j) = add;
        }
    }

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            printf( (j==2) ? "%d" : "%d ", *(*(ans+i)+j));
        }
        printf( (i==2) ? "" : "\n");
    }
    
    return 0;
}