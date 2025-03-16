#include <cstdio>

using namespace std;

// use the normal multiplication under n x n matrix
#define useStrassenThreshold 64
#define max(a,b) ((a) > (b) ? (a) : (b))


int** squareMatrixSum(int **A, int **B, int n) {
    int **C = new int*[n];
    for(int i=0; i<n; i++) {
        C[i] = new int[n];
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

int** squareMatrixSub(int **A, int **B, int n) {
    int **C = new int*[n];
    for(int i=0; i<n; i++) {
        C[i] = new int[n];
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

int** squareMatrixMul(int **A, int **B, int n) {
    int **C = new int*[n];
    for(int i=0; i<n; i++) {
        C[i] = new int[n];
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            C[i][j] = 0;
            for(int k=0; k<n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// cloest power of 2
int closestPowerOf2(int n) {
    int p = 1;
    while(p < n) {
        p *= 2;
    }
    return p;
}

int** strassenOfN(int** A, int** B, int n) {
    // base case
    if(n == 1) {
        int** C = new int*[1];
        C[0] = new int[1];
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // use the normal multiplication if the matrix is small
    if(n <= useStrassenThreshold) {
        return squareMatrixMul(A, B, n);
    }

    // divide the matrices
    int** A11 = new int*[n/2];
    int** A12 = new int*[n/2];
    int** A21 = new int*[n/2];
    int** A22 = new int*[n/2];
    int** B11 = new int*[n/2];
    int** B12 = new int*[n/2];
    int** B21 = new int*[n/2];
    int** B22 = new int*[n/2];

    for(int i=0; i<n/2; i++) {
        A11[i] = new int[n/2];
        A12[i] = new int[n/2];
        A21[i] = new int[n/2];
        A22[i] = new int[n/2];
        B11[i] = new int[n/2];
        B12[i] = new int[n/2];
        B21[i] = new int[n/2];
        B22[i] = new int[n/2];

        // copy the elements
        for(int j=0; j<n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+n/2];
            A21[i][j] = A[i+n/2][j];
            A22[i][j] = A[i+n/2][j+n/2];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+n/2];
            B21[i][j] = B[i+n/2][j];
            B22[i][j] = B[i+n/2][j+n/2];
        }
    }

    // calculate 7 matrices
    int** M1 = strassenOfN(squareMatrixSum(A11, A22, n/2), squareMatrixSum(B11, B22, n/2), n/2);
    int** M2 = strassenOfN(squareMatrixSum(A21, A22, n/2), B11, n/2);
    int** M3 = strassenOfN(A11, squareMatrixSub(B12, B22, n/2), n/2);
    int** M4 = strassenOfN(A22, squareMatrixSub(B21, B11, n/2), n/2);
    int** M5 = strassenOfN(squareMatrixSum(A11, A12, n/2), B22, n/2);
    int** M6 = strassenOfN(squareMatrixSub(A21, A11, n/2), squareMatrixSum(B11, B12, n/2), n/2);
    int** M7 = strassenOfN(squareMatrixSub(A12, A22, n/2), squareMatrixSum(B21, B22, n/2), n/2);

    // calculate the result matrices
    // C11 = M1 + M4 - M5 + M7
    int** C11 = squareMatrixSum(squareMatrixSub(squareMatrixSum(M1, M4, n/2), M5, n/2), M7, n/2);
    // C12 = M3 + M5
    int** C12 = squareMatrixSum(M3, M5, n/2);
    // C21 = M2 + M4
    int** C21 = squareMatrixSum(M2, M4, n/2);
    // C22 = M1 - M2 + M3 + M6
    int** C22 = squareMatrixSum(squareMatrixSum(squareMatrixSub(M1, M2, n/2), M3, n/2), M6, n/2);

    // merge the result matrices
    int** C = new int*[n];
    for(int i=0; i<n; i++) {
        C[i] = new int[n];
    }
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j+n/2] = C12[i][j];
            C[i+n/2][j] = C21[i][j];
            C[i+n/2][j+n/2] = C22[i][j];
        }
    }

    return C;
}

int** strassen(int** A, int** B, int a, int b, int c, int d) {
    // make the matrices square
    int n = max(max(a,b), max(c,d));
    n = closestPowerOf2(n);

    // fill the matrices with 0 to make them square
    int **A1 = new int*[n];
    int **B1 = new int*[n];
    for(int i=0; i<n; i++) {
        A1[i] = new int[n];
        B1[i] = new int[n];
    }

    // initialize the matrices
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            A1[i][j] = 0;
            B1[i][j] = 0;
        }
    }

    // copy original values
    for(int i=0; i<a; i++) {
        for(int j=0; j<b; j++) {
            A1[i][j] = A[i][j];
        }
    }
    for(int i=0; i<c; i++) {
        for(int j=0; j<d; j++) {
            B1[i][j] = B[i][j];
        }
    }
    return strassenOfN(A1, B1, n);
}


int main() {

    // read matrix sizes
    int a,b,c,d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    // read matrix A
    int **A = new int*[a];
    for(int i=0; i<a; i++) {
        A[i] = new int[b];
    }
    for(int i=0; i<a; i++) {
        for(int j=0; j<b; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    // read matrix B
    int **B = new int*[c];
    for(int i=0; i<c; i++) {
        B[i] = new int[d];
    }
    for(int i=0; i<c; i++) {
        for(int j=0; j<d; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // multiply the matrices
    int** C = strassen(A, B, a, b, c, d);

    // print the resuslt
    for(int i=0; i<a; i++) {
        for(int j=0; j<d; j++) {
            printf("%d%s", C[i][j], (i == a-1 && j == d-1) ? "\n" : " ");
        }
    }
    return 0;
}