#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <limits.h>

#define co coefficient
#define ex exponent
#define altoi(A) ((A)-'A')  // alpha to index
#define MAX_TERMS 10        // max terms of each polynominal can hold

typedef struct Poly {
    double coefficient;
    int exponent;
} Poly;

char *substr();
void readPoly();
void printPoly();
void Padd();
void Pmult();
void Peval();

// final element in array is reserved to record terms count
// polys[][MAX_TERMS].ex == terms count 
Poly polys[31][MAX_TERMS+1];  

int main() {
    char cmd;
    while(scanf("%c", &cmd)) {
        switch (cmd) {
        case '1':
            readPoly();
            break;
        case '2':
            printPoly();
            break;
        case '3':
            // Padd();
            break;
        case '4':
            // Pmult();
            break;
        case '5':
            // Peval();
            break;
        
        default:
            return 0;
        }

        fflush(stdin);
    }
    return 0;
}

char *substr(char* str, int n) {
    static char *sub;
    sub = malloc((n+1) * sizeof(char));
    strncpy(sub, str, n);
    sub[n] = '\0'; // place the null terminator
    return sub;
}

void readPoly() {
    char input[100];
    char *iptr = input;
    char alpha;

    fflush(stdin);
    scanf("%s", input);

    iptr = input;

    if(!isalpha(*iptr)) {
        printf("erro1 - %c\n", *iptr);
        readPoly();
        return;
    } else alpha = *iptr;

    iptr++;

    if(*iptr != '=') {
        printf("erro2 - %c\n", *iptr);
        readPoly();
        return;
    }

    iptr++;
    

    /* PROCESS polynominal */

    char *next;
    double dco;
    int iex;
    int len;
    int term=0;

    while(*iptr != '\0') {
        /* PROCESS coefficient */
        next = iptr;
        len=0;
        // FIND X
        while(1) {
            if(*next == '\0') {
                // no more x, CONSTANT only
                dco = atof(substr(iptr, len));
                break;
            }
            if(*next == 'x') {
                // check if term is -x or +x
                if(*(next-1) == '-' || *(next-1) == '+')
                    dco = (*(next-1) == '-') ? -1 : 1;
                else // n*x
                    dco = atof(substr(iptr, len));
                next++; // points to next term
                break;
            }
            next++, len++;
        }
        
        iptr = next;
        /* PROCESS exponent */
        // CONSTANT only
        if(*iptr == '\0' && *(iptr-1) != 'x') {
            iex = 0;
        }
        // FIND ^
        else if(*iptr == '^') {
            iptr++;
            next = iptr;
            len = 0;
            while(1) {
                if(*next == '\0' || (*next == '+' || *next == '-')) {
                    // end of a term
                    iex = atoi(substr(iptr, len));
                    break;
                }
                next++, len++;
            }
            iptr = next;
        } 
        // NO ^ (x^1)
        else if(*iptr == '\0' || (*iptr == '+' || *iptr == '-')) {
            iex = 1;
        }
        else {
            printf("erro3 - %c", *iptr);
            readPoly();
            return;
        }
        
        // store data
        polys[altoi(alpha)][term].co = dco;
        polys[altoi(alpha)][term].ex = iex;
        term++;

    }

    polys[altoi(alpha)][MAX_TERMS].ex = term;

}


void printPoly() {
    char c;

    printf("printPoly(): ");
    fflush(stdin);
    scanf("%c", &c);

    for(int t=0; t<polys[altoi(c)][MAX_TERMS].ex; t++) {
        Poly* term = &polys[altoi(c)][t];

        if((term->co >= 0 && t!=0))
            printf("+");
        printf("%.1lf", term->co);
        if(term->ex != 0)
            printf("x");
        if(term->ex != 0 && term->ex != 1)
            printf("^%d", term->ex);

        /*
        if(term->ex > 1) {
            if((term->co > 0 && t!=0))
                printf("+");
            printf("%lfx^%d", term->co, term->ex);
        } else if(term->ex == 1) {
            printf("%lfx", term->co);
        } else {
            printf("%lf", term->co);
        }
        */
    }

    printf("\n");
}


/*
    for(int i=0; i<polys[altoi(alpha)][MAX_TERMS].ex; i++) {
        printf("TEST polynominal | %lf | x^ | %d\n", polys[altoi(alpha)][i].co, polys[altoi(alpha)][i].ex);
    }

A=7x^5+2.3x^4+0.1x-5
B=3x^4+2.3x^2+x-5
C=2x^3+2.3x^2+x-5
*/