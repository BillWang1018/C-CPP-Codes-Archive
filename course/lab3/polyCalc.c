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
#define MAX_POLYS 30
// #define MAX_TERMS 10        // max terms of each polynominal can hold

#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define max(a,b)    (((a) > (b)) ? (a) : (b))

typedef struct Polynominal {
    double coefficient;
    int exponent;
    struct Polynominal *nterm;
} Poly;

void delList(char);
void pushList(char, double, int);
void push(Poly**, double, int);

char *substr();
void readPoly();
void printPoly();
void Padd();
void Pmult();
void Peval();

// final element in array is reserved to record terms count
// polys_array[][MAX_TERMS].ex == terms count 
// Poly polys_array[MAX_POLYS][MAX_TERMS+1];
// using list
Poly *polyHead[MAX_POLYS]={0};
Poly *polyBack[MAX_POLYS]={0};

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
            Padd();
            break;
        case '4':
            // Pmult();
            break;
        case '5':
            Peval();
            break;
        
        default:
            return 0;
        }

        fflush(stdin);
    }
    return 0;
}



void delList(char i) {
    Poly *cur = polyHead[i], *tmp;
    if(cur == NULL) return;
    while(cur != NULL) {
        tmp = cur->nterm;
        free(cur);
        cur = tmp;
    }
    polyHead[i] = NULL;
    polyBack[i] = NULL;
}

void pushList(char i, double co, int ex) {
    Poly *node = (Poly *)malloc(sizeof(Poly));
    node->co = co;
    node->ex = ex;
    node->nterm = NULL;

    if(polyBack[i] == NULL) {
        polyBack[i] = node;
        polyHead[i] = node;
    } else {
        polyBack[i]->nterm = node;
        polyBack[i] = node;
    }

}

void push(Poly **head, double co, int ex) {
    Poly *node = (Poly *)malloc(sizeof(Poly));
    node->co = co;
    node->ex = ex;
    node->nterm = NULL;


    if(*head == NULL) {
        *head = node;
    } else {
        Poly *tmp = *head;
        while(tmp->nterm != NULL) {
            tmp = tmp->nterm;
        }
        tmp->nterm = node;
    }

}

char *substr(char* str, int n) {
    static char *sub;
    sub = malloc((n+1) * sizeof(char));
    strncpy(sub, str, n);
    sub[n] = '\0'; // place the null terminator
    return sub;
}

void printfPoly(Poly **head) {
    char firstTerm = 1;
    Poly **tmp = head;
    while((*tmp) != NULL) {

        if((*tmp)->co >= 0 && !firstTerm)
            printf("+");
        printf("%.1lf", (*tmp)->co);
        if((*tmp)->ex != 0)
            printf("x");
        if((*tmp)->ex != 0 && (*tmp)->ex != 1)
            printf("^%d", (*tmp)->ex);

        (*tmp) = (*tmp)->nterm;

        firstTerm = 0;

    }

    printf("\n");
}

/* POLYNOMINALS METHODS START FROM HERE */

void readPoly() {
    char input[100];
    char *iptr = input;
    char alpha;

    fflush(stdin);
    scanf("%s", input);

    iptr = input;

    if(!isalpha(*iptr)) {
        printf("erro1 at - %c\n", *iptr);
        readPoly();
        return;
    } else alpha = *iptr;

    iptr++;

    if(*iptr != '=') {
        printf("erro2 at - %c\n", *iptr);
        readPoly();
        return;
    }

    iptr++;
    

    /* PROCESS polynominal */

    char *next;
    double dco=0;
    int iex=0;
    int len=0;
    // int term=0;
    alpha = altoi(alpha);
    delList(alpha);

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
                // check if term is -x or +x or x
                if((*(next-1) == '-' || *(next-1) == '+') || *(next-1) == '=')
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
            printf("erro3 at - %c", *iptr);
            readPoly();
            return;
        }
        
        // store data
        pushList(alpha, dco, iex);
        // polys_array[alpha][term].co = dco;
        // polys_array[alpha][term].ex = iex;
        // term++;

    }

    // polys_array[alpha][MAX_TERMS].ex = term;

}

void printPoly() {
    char c;
    Poly *node;

    printf("printPoly(): ");
    fflush(stdin);
    scanf("%c", &c);
    c = altoi(c);
    node = polyHead[c];

    printfPoly(&node);
}
/*
void printPoly() {
    char c;

    printf("printPoly(): ");
    fflush(stdin);
    scanf("%c", &c);

    for(int t=0; t<polys_array[altoi(c)][MAX_TERMS].ex; t++) {
        Poly* term = &polys_array[altoi(c)][t];

        if((term->co >= 0 && t!=0))
            printf("+");
        printf("%.1lf", term->co);
        if(term->ex != 0)
            printf("x");
        if(term->ex != 0 && term->ex != 1)
            printf("^%d", term->ex);

    }
    printf("\n");
}
*/

void Padd() {
    char c1, c2;
    fflush(stdin);
    printf("Enter two polynominals to add: ");
    scanf("%c %c", &c1, &c2);
    c1 = altoi(c1), c2 = altoi(c2);
    Poly *ans = NULL, **ansHead = &ans;
    Poly *p1 = polyHead[c1], *p2 = polyHead[c2];
    if(p1 == NULL || p2 == NULL) {
        printf("The variable(s) is empty!\n");
        return;
    }
    while(p1 != NULL || p2 != NULL) {
        if(p1 == NULL) {
            push(&ans, p2->co, p2->ex);
            p2 = p2->nterm;
            continue;
        }
        if(p2 == NULL) {
            push(&ans, p1->co, p1->ex);
            p1 = p1->nterm;
            continue;
        }

        if(p1->ex > p2->ex) {
            push(&ans, p1->co, p1->ex);
            p1 = p1->nterm;
        } else
        if(p1->ex < p2->ex) {
            push(&ans, p2->co, p2->ex);
            p2 = p2->nterm;
        } else
        if(p1->ex == p2->ex) {
            push(&ans, (p1->co + p2->co), p1->ex);
            p1 = p1->nterm;
            p2 = p2->nterm;
        }
    }

    printfPoly(ansHead);

}

void Peval() {
    double x, ans=0;
    char c;
    fflush(stdin);
    scanf("%lf %c", &x, &c);
    c = altoi(c);
    Poly *p = polyHead[c];
    while(p != NULL) {
        ans += p->co * pow(x, p->ex);
        p = p->nterm;
    }

    printf("%lf\n", ans);


}



/*
1 
A=x
1
B=12x^2-3x+3.2
1
C=-5x^10+4x-1.2
1
D=-x+11


A=7x^5+2.3x^4+0.1x-5
B=3x^4+2.3x^2+x-5
C=2x^3+2.3x^2+x-5
*/