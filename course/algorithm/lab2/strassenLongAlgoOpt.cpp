#include <cstdio>
#include <cstring>

using namespace std;

// use the normal multiplication under n x n matrix
#define useStrassenThreshold 2
#define max(a,b) ((a) > (b) ? (a) : (b))
typedef long long int ll;

void squareMatrixSum(const ll *A, const ll *B, ll *C, int n) {
    memset(C, 0, n * n * sizeof(ll)); // initialize matrix C with 0

    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] + B[i];
    }
}

void squareMatrixSub(const ll *A, const ll *B, ll *C, int n) {
    memset(C, 0, n * n * sizeof(ll)); // initialize matrix C with 0

    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] - B[i];
    }
}

void squareMatrixMul(const ll *A, const ll *B, ll *C, int n) {
    memset(C, 0, n * n * sizeof(ll)); // initialize matrix C with 0
    
    // Loop order optimization for better cache utilization
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            ll temp = A[i * n + k];  // Reduce memory access
            for (int j = 0; j < n; j++) {
                C[i * n + j] += temp * B[k * n + j];  
            }
        }
    }
}

// closest power of 2
int closestPowerOf2(int n) {
    int p = 1;
    while (p < n) {
        p *= 2;
    }
    return p;
}

// convert the matrix to 4 submatrices
// [A11], [A12], [A21], [A22]
void toFourMatrix(ll *subMatrices, const ll* A, int n) {
    int newSize = n / 2;
    int partSize = newSize * newSize;

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            subMatrices[i * newSize + j] = A[i * n + j];
            subMatrices[i * newSize + j + partSize] = A[i * n + j + newSize];
            subMatrices[i * newSize + j + 2 * partSize] = A[(i + newSize) * n + j];
            subMatrices[i * newSize + j + 3 * partSize] = A[(i + newSize) * n + j + newSize];
        }
    }
}

void strassenOfN(const ll* A, const ll* B, ll* C, int n) {
    // base case
    if (n <= useStrassenThreshold) {  
        squareMatrixMul(A, B, C, n);
        return;
    }

    int newSize = n / 2;
    int partSize = newSize * newSize;

    ll *tempStorage = new ll[(7 + 2) * partSize]; // M1-M7 + temp1 + temp2
    ll *subA = new ll[n * n]; // to store the submatrices (ABC)
    ll *subB = new ll[n * n];
    
    // divide the matrices
    toFourMatrix(subA, A, n);
    toFourMatrix(subB, B, n);
    
    ll *A11 = subA;
    ll *A12 = A11 + partSize;
    ll *A21 = A12 + partSize;
    ll *A22 = A21 + partSize;
    
    ll *B11 = subB;
    ll *B12 = B11 + partSize;
    ll *B21 = B12 + partSize;
    ll *B22 = B21 + partSize;
    
    
    ll *M1 = tempStorage;
    ll *M2 = M1 + partSize;
    ll *M3 = M2 + partSize;
    ll *M4 = M3 + partSize;
    ll *M5 = M4 + partSize;
    ll *M6 = M5 + partSize;
    ll *M7 = M6 + partSize;
    
    ll *temp1 = M7 + partSize;
    ll *temp2 = temp1 + partSize;
    
    // M1 = (A11 + A22) * (B11 + B22)
    squareMatrixSum(A11, A22, temp1, newSize);
    squareMatrixSum(B11, B22, temp2, newSize);
    strassenOfN(temp1, temp2, M1, newSize);
    // M2 = (A21 + A22) * (B11)
    squareMatrixSum(A21, A22, temp1, newSize);
    strassenOfN(temp1, B11, M2, newSize);
    // M3 = (A11) * (B12 - B22)
    squareMatrixSub(B12, B22, temp1, newSize);
    strassenOfN(A11, temp1, M3, newSize);
    // M4 = (A22) * (B21 - B11)
    squareMatrixSub(B21, B11, temp1, newSize);
    strassenOfN(A22, temp1, M4, newSize);
    // M5 = (A11 + A12) * (B22)
    squareMatrixSum(A11, A12, temp1, newSize);
    strassenOfN(temp1, B22, M5, newSize);
    // M6 = (A21 - A11) * (B11 + B12)
    squareMatrixSub(A21, A11, temp1, newSize);
    squareMatrixSum(B11, B12, temp2, newSize);
    strassenOfN(temp1, temp2, M6, newSize);
    // M7 = (A12 - A22) * (B21 + B22)
    squareMatrixSub(A12, A22, temp1, newSize);
    squareMatrixSum(B21, B22, temp2, newSize);
    strassenOfN(temp1, temp2, M7, newSize);
    
    delete[] subA; delete[] subB;

    // calculate the result matrices
    ll *subC = new ll[n * n];

    ll *C11 = subC;
    ll *C12 = C11 + partSize;
    ll *C21 = C12 + partSize;
    ll *C22 = C21 + partSize;
    // C11 = M1 + M4 - M5 + M7
    squareMatrixSum(M1, M4, temp1, newSize);
    squareMatrixSub(temp1, M5, temp2, newSize);
    squareMatrixSum(temp2, M7, C11, newSize);
    // C12 = M3 + M5
    squareMatrixSum(M3, M5, C12, newSize);
    // C21 = M2 + M4
    squareMatrixSum(M2, M4, C21, newSize);
    // C22 = M1 - M2 + M3 + M6
    squareMatrixSub(M1, M2, temp1, newSize);
    squareMatrixSum(temp1, M3, temp2, newSize); 
    squareMatrixSum(temp2, M6, C22, newSize);

    delete[] tempStorage;
    
    // merge the result matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i * n + j] = C11[i * newSize + j];
            C[i * n + j + newSize] = C12[i * newSize + j];
            C[(i + newSize) * n + j] = C21[i * newSize + j];
            C[(i + newSize) * n + j + newSize] = C22[i * newSize + j];
        }
    }
    delete[] subC;
}

void prettyPrintMatrix(const ll *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lld%s", A[i * n + j], (j == n - 1) ? "\n" : " ");
        }
    }
}

int main() {
    // read matrix sizes
    int a, b, c, d, n;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    n = closestPowerOf2(max(max(a, b), max(c, d)));
    
    ll *A = new ll[n * n];
    ll *B = new ll[n * n];
    ll *C = new ll[n * n]; // result matrix

    // initialize the matrices with 0
    memset(A, 0, n * n * sizeof(ll)); 
    memset(B, 0, n * n * sizeof(ll));
    memset(C, 0, n * n * sizeof(ll));

    // read matrix A
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            scanf("%lld", &A[i * n + j]);
        }
    }

    // read matrix B
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%lld", &B[i * n + j]);
        }
    }

    // multiply the matrices
    strassenOfN(A, B, C, n);

    // print the result
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < d; j++) {
            printf("%lld%s", C[i * n + j], (i == a-1) && (j == d-1) ? "" : " ");
        }
    }

    // free the memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}