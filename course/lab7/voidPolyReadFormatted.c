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

PolyNodePtr clearPoly(PolyNodePtr *node) {
    PolyNodePtr nptr = *node;
    while(nptr->next) {
        nptr = nptr->next;
        free(*node);
        *node = nptr;
    }
    free(*node);
    *node = NULL;
}

void pushPolyNode(PolyNodePtr *node, int coe, int exp) {
    PolyNodePtr nptr = *node;
    PolyNodePtr newNode = newPolyNode(coe, exp);
    if(!*node) {
        *node = newNode;
        // printf("d | %d %d | at-%p\n", (*node)->coe, (*node)->exp, *node);
        return;
    }

    while(nptr->next) {
        nptr = nptr->next;
    }
    nptr->next = newNode;
}

void readPoly(Poly* polys, int *idx, char *input) {
    int prevExp=2147483647;
    char *iptr = input;
    char ch, prev, next, num[15], *nump;
    
    // check if first char. is alphabet 
    ch = *iptr;
    if(!isalpha(ch)) {
        printf("Error - First char not alpha. - %c\n", ch); 
        *idx = -1;
        return;
    }
    for(*idx=0; *idx<MAX_POLYS; (*idx)++) {
        if(polys[*idx].head == NULL) break;
        if(polys[*idx].name == ch) {
            clearPoly(&polys[*idx].head);
            break;
        }
        if(*idx == MAX_POLYS-1) {
            printf("FULL\n");
            *idx = -1;
            return;
        }
    }
    prev = *iptr++;
    next = *iptr;

    // check if second char is equal sign
    if(next != '=') {
        printf("Equal sign not detected - %c\n", *iptr);
        *idx = -1;
        return;
    }
    prev = *iptr++;
    next = *iptr;

    if(next == '\0') {
        printf("NULL expression!\n");
        *idx = -1;
        return;
    }

    /* PROCESS polynominal */
    int coe=0;
    int exp=0;

    while(next != '\0') {
        // printf("b | %c\n", next);
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
            else if(tolower(next) == 'x') {
                // check if term is -x or +x or x (coe. is 1 or -1)
                if(prev == '+' || prev == '=') {
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
            else if(isdigit(next) || (next == '+' || next == '-')) {
                *nump++ = next;
                prev = *iptr++;
                next = *iptr;
            }
            else {
                printf("Illegel expression 1 - %c\n", next);
                *idx = -1;
                return;
            }
        }
        
        if(next != '\0') {
            prev = *iptr++;
            next = *iptr;
        }

        /* PROCESS exponent */
        // is constant
        if(next == '\0' && tolower(prev) != 'x') {
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
                else if (isdigit(next)) {
                    *nump++ = next;
                    prev = *iptr++;
                    next = *iptr;
                }
                else {
                    printf("Illegel expression 2 - %c\n", next);
                    *idx = -1;
                    return;
                }
            }
        }
        // no "^" (x^1)
        else if(next == '\0' || (next == '+' || next == '-')) {
            exp = 1;
        }
        // the input is illegal 
        else if(!isdigit(next)) {
            printf("Illegel expression 3 - %c\n", next);
            *idx = -1;
            return;
        }

        if(prevExp <= exp) {
            printf("ERROR\n");
            *idx = -1;
            return;
        }
        prevExp = exp;
        // store data
        // printf("d | store data %d\n", *idx);
        pushPolyNode(&polys[*idx].head, coe, exp);
    }
    polys[*idx].name = ch;
}

void printPair(PolyNodePtr poly) {
    PolyNodePtr nptr = poly;
    while(nptr != NULL) {
        printf("%d %d\n", nptr->coe, nptr->exp);
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
    
    char input[100];
    while (scanf("%s", input) != EOF) {
        if(input[0] == '0') break;

        int idx;
        readPoly(polys, &idx, input);
        if(idx < 0) continue;
        printf("%c\n", polys[idx].name);
        printPair(polys[idx].head);
    }
    printf("quit\n");


    return 0;
}
