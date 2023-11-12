#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_POLYS 10

typedef struct PolyNode {
    int coe;
    int exp;
    struct PolyNode *next;
} PolyNode;

typedef struct Poly {
    char name;
    struct PolyNode *head;
} Poly;

typedef PolyNode * PolyNodePtr;

PolyNodePtr newPolyNode(int coe, int exp) {
    PolyNodePtr node = (PolyNodePtr) malloc( sizeof(PolyNode) );
    node->coe = coe;
    node->exp = exp;
    node->next = NULL;
    return node;
}

void pushPolyNode(PolyNodePtr *node, int coe, int exp) {
    PolyNodePtr nptr = *node;
    PolyNodePtr newNode = newPolyNode(coe, exp);
    if(!*node) {
        printf("d | create new head\n");
        *node = newNode;
        printf("d | %d %d | at-%p\n", (*node)->coe, (*node)->exp, *node);
        return;
    }

    while(nptr->next) {
        nptr = nptr->next;
    }
    printf("d | push node\n");
    nptr->next = newNode;
}

void readPoly(Poly* polys) {
    char input[100];

    printf("readPoly():\n");
    scanf("%s", input);

    char *iptr = input;
    char ch, prev, next, num[10], *nump;
    
    // check if first char. is alphabet 
    ch = *iptr;
    if(!isalpha(ch)) {
        printf("Error - First char not alpha. - %c\n", ch); 
        return;
    }
    int idx=0;
    for(; idx<MAX_POLYS; idx++) {
        if(polys->head == NULL) break;
        if(polys->name == ch) {
            printf("Error - The name has been used - %c\n", ch);
            return;
        }
    }
    prev = *iptr++;
    next = *iptr;

    // check if second char is equal sign
    if(next != '=') {
        printf("Equal sign not detected - %c\n", *iptr);
        return;
    }
    prev = *iptr++;
    next = *iptr;

    /* PROCESS polynominal */
    int coe=0;
    int exp=0;

    while(next != '\0') {
        nump = num;

        /* PROCESS coefficient */
        // find next "x"
        while(1) {
            // no "x", rest of the numbers is constant (x^0)
            if(next == '\0') {
                *nump = '\0';
                coe = atoi(num);
                break;
            }
            // found "x"
            if(next == 'x') {
                // check if term is -x or +x or x (coe. is 1 or -1)
                if( prev == '+' || prev == '=') {
                    coe = 1;
                    break;
                }
                else if( prev == '-' ) {
                    coe = -1;
                    break;
                }
                else {// coe. is numbers before x
                    *nump = '\0';
                    coe = atoi(num);
                    break;
                }
                prev = *iptr++;
                next = *iptr;
            }
            *nump++ = next;
            prev = *iptr++;
            next = *iptr;
        }
        
        prev = *iptr++;
        next = *iptr;

        /* PROCESS exponent */
        // is constant
        if(next == '\0' && prev != 'x') {
            exp = 0;
        }
        // find "^"
        else if(next == '^') {
            prev = *iptr++;
            next = *iptr;
            nump = num;
            while(1) {
                // end of a term
                if(next == '\0' || (next == '+' || next == '-')) {
                    *nump = '\0';
                    exp = atoi(num);
                    break;
                }
                *nump++ = next;
                prev = *iptr++;
                next = *iptr;
            }
            // prev = *iptr++;
            // next = *iptr;
        } 
        // no "^" (x^1)
        else if(next == '\0' || (next == '+' || next == '-')) {
            exp = 1;
        }
        // the input is illegal 
        else {
            printf("Illegel expression\n");
            return;
        }
        
        // store data
        printf("d | store data %d\n", idx);
        pushPolyNode(&polys[idx].head, coe, exp);
    }
    polys[idx].name = ch;
}

void printPair(PolyNodePtr poly) {
    PolyNodePtr nptr = poly;
    printf("HEAD | %p\n", nptr);
    while(nptr != NULL) {
        printf("%d %d | next-%p\n", nptr->coe, nptr->exp, nptr->next);
        nptr = nptr->next;
    }
}


int main() {
    int polyCount = 0;
    Poly *polys = (Poly*) malloc( sizeof(Poly) * MAX_POLYS );
    for(int i=0; i<MAX_POLYS; i++) {
        polys[i].head = NULL; // init
        polys[i].name = 0;
    }

    readPoly(polys);
    printf("char: %c\n", polys[0].name);
    printPair(polys[0].head);


    return 0;
}
