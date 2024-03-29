#define INIT_SIZE 50
#define MAX_COL   1000
#define index(A) ((A)-'A')

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lld;

typedef struct {
    int row;
    int col;
    lld val;
} Term;

// mats[n][0] stores information, index of row/col starts from 1
Term *mats[30] = {0};

// Append matrix by INIT_SIZE
void appendMatrix(Term **);
// Push a term to the back (term_list, col, row, val)
void pushTerm(Term **, int, int, lld);
//reset term_list and it's size
void resetMatrix(Term **);
//Debug
void debugPrint();

// Enter a sparse matrix and assign it to A or B
void readSparseMatrixs();
// Give a matrix label and print it out 
void printSingleMatrix(Term *);
// Add two matrix together and print it out
Term* addSparseMatrix();
// Print and return transpose result of a matrix
Term* fastTranspose();
// Multiply two sparse matrixs and print out and return the result
Term* matrixMultiply();


int main() {

    while(1) {
        printf(
            "-------->FUNCTIONS<--------\n"
            "1. Key in sparse matrix\n"
            "2. Print sparse matrix\n"
            "3. Add sparse matrixs\n"
            "4. Transform sparse matrix\n"
            "5. Multiply sparse matrix\n"
            "----------------<|SELECTION: "
        );
        char c, var;
        // * means to discard, %*c to discard extra \n 
        scanf("%c%*c", &c);
        switch (c) {
            case '1':
                readSparseMatrixs();
                break;
            case '2':
                scanf("%c%*c", &var);
                var -= 'A';
                
                if (!mats[var]) {
                    printf("The matrix isn't created\n");
                    break;
                }

                printSingleMatrix(mats[var]);
                break;
            case '3':
                addSparseMatrix();
                break;
            case '4':
                fastTranspose();
                break;
            case '5':
                matrixMultiply();
                break;
            case '6':
                return 0;
            default:
                printf("default\n");
        }

    }
    return 0;
}



void appendMatrix(Term **mat) {
    Term *tmp;
    if(*mat) {
        printf("Not null, realloc size to: %d\n", (INIT_SIZE + (*mat)[0].val));
        tmp = (Term*) realloc(*mat, sizeof(Term) * (INIT_SIZE + (*mat)[0].val));
    }
    else {
        printf("Null, mallocing new mem, size=%d\n", INIT_SIZE+1);
        tmp = (Term*) malloc (sizeof(Term) * (INIT_SIZE + 1));
    }
    
    printf("Append size to %d\n", INIT_SIZE + ((*mat)==NULL ? 1 : (*mat)[0].val));
    
    if(tmp == NULL) {
        printf("ERROR REQUEST MEM\n");
        free(tmp);
        return;
    }

    *mat = tmp;
    
}

void pushTerm(Term **mat, int col, int row, lld val) {
    if (!val) return; // don't need to record
    if (!*mat)
        resetMatrix(mat);
    if ((*mat)[0].val % INIT_SIZE == 1 && (*mat)[0].val >= INIT_SIZE)
        appendMatrix(mat);
    int last = ++(*mat)[0].val;
    (*mat)[last].col = col;
    (*mat)[last].row = row;
    (*mat)[last].val = val;
    // printf("Add an entry at %d: (%d, %d | val=%lld)\n", last, col, row, val);
}

void resetMatrix(Term **mat) {
    // free(mat[var]);... // having problem with free() QAQ
    // debugPrint(*mat);
    if (!(*mat)) 
        appendMatrix(mat);
    (*mat)[0].col = 0;
    (*mat)[0].row = 0;
    (*mat)[0].val = 0;
}

void debugPrint(Term *mat) {
    if(!mat) {
        printf("NULL\n");
        return;
    }
    printf("COL=%d | ROW=%d | CNT=%lld\n", mat[0].col, mat[0].row, mat[0].val);
    for(int i=1; i<=mat[0].val; i++) {
        printf("(%d, %d) = %lld\n", mat[i].col, mat[i].row, mat[i].val);
    }
}

void readSparseMatrixs() {
    char var;
    scanf("%c%*c", &var);
    var -= 'A';

    int COL, ROW, count;
    lld n;
    scanf("%d%d%*c", &COL, &ROW);

    while(1) {
        count = 0;
        resetMatrix(&mats[var]);
        for(int col=1; col<=COL; col++) {
            for(int row=1; row<=ROW; row++) {
                scanf("%lld", &n);
                if(n) {
                    pushTerm(&mats[var], col, row, n);
                    count++;
                }
            }
            scanf("%*c");
        }

        if(count > (COL*ROW)/2) {
            printf("Error. Please try again.\n");
            continue;
        } else {
            printf("Is a Sparse Matrix.\n");
            break;
        }
    }

    mats[var][0].col = COL;
    mats[var][0].row = ROW;

    // printf("mats[var][0] = (%d, %d, %d)\n", COL, ROW, count);
    // printf("mats[var][1] = (%d, %d, %d)\n", mats[var][1].col, mats[var][1].row, mats[var][1].val);
}

void printSingleMatrix(Term *mat) {

    debugPrint(mat);

    int COL = mat[0].col;
    int ROW = mat[0].row;
    int nzeroCnt = mat[0].val;
    lld ans[COL+1][ROW+1];
    memset(ans, 0, (COL+1)*(ROW+1)*sizeof(lld));
    Term *tptr = &mat[1];

    while(nzeroCnt--) {
        ans[tptr->col][tptr->row] = tptr->val;
        tptr++;
    }

    for(int col=1; col<=COL; col++) {
        for(int row=1; row<=ROW; row++) {
            printf("%lld ", ans[col][row]);
        }
        printf("\n");
    }

}

Term *addSparseMatrix() {
    Term *ans = NULL;
    resetMatrix(&ans);

    char a, b;
    scanf("%c %c%*c", &a, &b);
    a -= 'A', b -= 'A';

    if(mats[a] == NULL || mats[b] == NULL) {
        printf("Some matrix doesn't exist\n");
        return NULL;
    }
    if(mats[a][0].col != mats[b][0].col || mats[a][0].row != mats[b][0].row) {
        printf("These matrixs aren't capable of adding\n");
        return NULL;
    }
    
    int sumval=0;
    int COL = mats[a][0].col;
    int ROW = mats[a][0].row;
    ans[0].col = COL, ans[0].row = ROW;
    int a_nzeroCnt = mats[a][0].val;
    int b_nzeroCnt = mats[b][0].val;
    Term *a_tptr = &mats[a][1];
    Term *b_tptr = &mats[b][1];

    debugPrint(mats[a]);
    debugPrint(mats[b]);

    for(int col=1; col<=COL; col++) {
        for(int row=1; row<=ROW; row++) {
            sumval = 0;
            if(a_nzeroCnt && (col == a_tptr->col && row == a_tptr->row)) {
                sumval += a_tptr->val;
                a_tptr++, a_nzeroCnt--;
            }
            if(b_nzeroCnt && (col == b_tptr->col && row == b_tptr->row)) {
                sumval += b_tptr->val;
                b_tptr++, b_nzeroCnt--;
            }
            pushTerm(&ans, col, row, sumval);
        }
    }

    printSingleMatrix(ans);

    return ans;
}

Term *fastTranspose() { 
    Term *ans = NULL;
    resetMatrix(&ans);

    char a;
    scanf("%c%*c", &a);
    a -= 'A';
    if(mats[a] == NULL) {
        printf("Matrix doesn't exist\n");
        return NULL;
    }
    ans[0].col = mats[a][0].row;
    ans[0].row = mats[a][0].col;
    ans[0].val = mats[a][0].val;
    if(ans[0].val > INIT_SIZE)
        appendMatrix(&ans);
    
    int nzeroRow[MAX_COL+1] = {0}, startingPos[MAX_COL+1] = {0};

    for(int i=1; i <= mats[a][0].val; i++) {
        nzeroRow[mats[a][i].col]++;
    }

    startingPos[0] = 1;
    for(int i=1; i <= mats[a][0].col; i++) {
        startingPos[i] = startingPos[i-1] + nzeroRow[i-1];
    }

    for(int i=1; i <= mats[a][0].val; i++) {
        int j = startingPos[mats[a][i].col]++;
        ans[j].col = mats[a][i].row;
        ans[j].row = mats[a][i].col;
        ans[j].val = mats[a][i].val;
    }

    printSingleMatrix(ans);

    return ans;
}

Term *matrixMultiply() {
    Term *ans = NULL;
    resetMatrix(&ans);

    char a, b;
    scanf("%c %c%*c", &a, &b);
    a -= 'A', b -= 'A';

    if(mats[a] == NULL || mats[b] == NULL) {
        printf("Some matrix doesn't exist\n");
        return NULL;
    }
    if(mats[a][0].row != mats[b][0].col) {
        printf("These matrixs aren't capable of multiplying\n");
        return NULL;
    }
    
    int sumval=0;
    int COL = mats[a][0].col;
    int ROW = mats[b][0].row;
    int I = mats[a][0].row;
    ans[0].col = COL, ans[0].row = ROW;
    int a_nzeroCnt = mats[a][0].val;
    int b_nzeroCnt = mats[b][0].val;
    Term *a_tptr = &mats[a][1];
    Term *b_tptr = &mats[b][1];

    debugPrint(mats[a]);
    debugPrint(mats[b]);

    for(int col=1; col<=COL; col++) {
        for(int row=1; row<=ROW; row++) {
            sumval = 0;
            a_nzeroCnt = mats[a][0].val;
            b_nzeroCnt = mats[b][0].val;
            a_tptr = &mats[a][1];
            b_tptr = &mats[b][1];
            for(int i=1; i<=I; i++) {
                while(a_nzeroCnt && (a_tptr->col < col || a_tptr->row < i))
                    a_tptr++, a_nzeroCnt--; // proceed to next
                while(b_nzeroCnt && (b_tptr->row < row || b_tptr->col < i))
                    b_tptr++, b_nzeroCnt--; // proceed to next

                // printf("col=%d | row=%d | i=%d || a_ptr(%d, %d)=%lld || b_ptr(%d, %d)=%lld\n", col, row, i, a_tptr->col, a_tptr->row, a_tptr->val, b_tptr->col, b_tptr->row, b_tptr->val);

                if ((!a_nzeroCnt && a_tptr->col != col) || !b_nzeroCnt && b_tptr->row != row)
                    break;
                if ((a_tptr->col == col && a_tptr->row == i) && 
                    (b_tptr->col == i && b_tptr->row == row)) {
                   sumval += a_tptr->val * b_tptr->val; 
                }
            }
            pushTerm(&ans, col, row , sumval);
        }
    }

    printSingleMatrix(ans);

    return ans;
}

//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \ 
//                / _||||| -:- |||||- \ 
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG

/*

1
A
3 3
1 2 3
4 0 0
0 0 0
1
B
3 3
0 0 1
0 0 0
3 2 1

*/