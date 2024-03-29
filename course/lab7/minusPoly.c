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
    if(!coe) return;
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
            *idx = -2;
            return;
        }
    }
    prev = *iptr++;
    next = *iptr;

    // check if second char is equal sign
    if(next != '=') {
        *idx = -1;
        return;
    }
    prev = *iptr++;
    next = *iptr;

    if(next == '\0') {
        *idx = -1;
        return;
    }

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
                else { // coe. is numbers before x
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
                *idx = -1;
                return;
            }
        }
        
        if(coe == 0) { // can't be 0
            *idx = -1;
            return;
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
            *idx = -1;
            return;
        }

        if(prevExp <= exp) {
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

void printPoly(Poly poly) {
    int coe, exp;
    PolyNodePtr head = poly.head;
    PolyNodePtr nptr = head;
    while(nptr != NULL) {
        coe = nptr->coe;
        exp = nptr->exp;
        if(coe == 1) {
            if(nptr == head) {
                printf("");
            } else if (exp == 0) {
                printf("+1");
            } else {
                printf("+");
            }
        }
        else if(coe == -1) {
            if(exp == 0) {
                printf("-1");
            } else {
                printf("-");
            }
        } 
        else {
            if(nptr == head) {
                printf("%d", coe);
            } else {
                printf("%s%d", (coe > 0 ? "+" : ""), coe);
                
            }
        }

        if(exp == 0) {
            printf("");
        }
        else if(exp == 1) {
            printf("x");
        } 
        else {
            printf("x^%d", exp);
        }

        nptr = nptr->next;
    }
    printf("\n");
}

void printAllPolys(Poly *polys) {
    if(!polys[0].head) {
        printf("NO POLY\n");
        return;
    }
    for(int i=0; i<MAX_POLYS; i++) {
        if(polys[i].head) {
            printPoly(polys[i]);
        } else break;
    }
}

PolyNodePtr addPoly(PolyNodePtr polyA, PolyNodePtr polyB) {
    PolyNodePtr pa = polyA, pb = polyB;
    PolyNodePtr sum = NULL;
    while(pa || pb) {
        if(pa && !pb) { // only A
            pushPolyNode(&sum, pa->coe, pa->exp);
            pa = pa->next;
            continue;
        }
        if(!pa && pb) { // only B
            pushPolyNode(&sum, pb->coe, pb->exp);
            pb = pb->next;
            continue;
        }
        
        if(pa->exp > pb->exp) {
            pushPolyNode(&sum, pa->coe, pa->exp);
            pa = pa->next;
            continue;
        }
        if(pb->exp > pa->exp) {
            pushPolyNode(&sum, pb->coe, pb->exp);
            pb = pb->next;
            continue;
        }
        if(pa->exp == pb->exp) {
            pushPolyNode(&sum, pa->coe + pb->coe, pa->exp);
            pa = pa->next;
            pb = pb->next;
            continue;
        }
    }
    return sum;
}

PolyNodePtr minusPoly(PolyNodePtr polyA, PolyNodePtr polyB) {
    PolyNodePtr pa = polyA, pb = polyB;
    PolyNodePtr sum = NULL;
    while(pa || pb) {
        if(pa && !pb) { // only A
            pushPolyNode(&sum, pa->coe, pa->exp);
            pa = pa->next;
            continue;
        }
        if(!pa && pb) { // only B
            pushPolyNode(&sum, -pb->coe, pb->exp);
            pb = pb->next;
            continue;
        }
        
        if(pa->exp > pb->exp) {
            pushPolyNode(&sum, pa->coe, pa->exp);
            pa = pa->next;
            continue;
        }
        if(pb->exp > pa->exp) {
            pushPolyNode(&sum, -pb->coe, pb->exp);
            pb = pb->next;
            continue;
        }
        if(pa->exp == pb->exp) {
            pushPolyNode(&sum, pa->coe - pb->coe, pa->exp);
            pa = pa->next;
            pb = pb->next;
            continue;
        }
    }
    return sum;
}

void addPolyExp(Poly* polys, int *idx, char *input) {
    char *iptr = input;
    char ch, ca, cb;
    int fch, fa, fb; //flags
    fch = fa = fb = -1; // -1 = not found
    
    // check if first char. is alphabet 
    ch = *iptr;
    if(!isalpha(ch)) {
        *idx = -1;
        return;
    }
    
    iptr++;
    if(*iptr == '+') {
        ca = ch;
        cb = *++iptr;
        ch = 0;
        fch = -2; // don't seek
    } else if(*iptr == '=') {
        ca = *++iptr;
        if(*++iptr != '+') {
            *idx = -1;
            return;
        }
        cb = *++iptr;
    } else {
        *idx = -1;
        return;
    }

    for(*idx=0; *idx<MAX_POLYS; (*idx)++) {
        if(polys[*idx].head == NULL) {
            if(fch == -1)
                fch = *idx;
            break;
        }
        if(polys[*idx].name == ch) {
            fch = *idx;
        }
        if(polys[*idx].name == ca) {
            fa = *idx;
        }
        if(polys[*idx].name == cb) {
            fb = *idx;
        }
        
        if((fa!=-1 && fb!=-1) && fch!=-1) {
            break;
        }

        if(*idx == MAX_POLYS-1) {
            *idx = -2;
            return;
        }
    }

    if(fa==-1 || fb==-1) {
        *idx = -1;
        return;
    }
    
    Poly poly;
    poly.head = addPoly(polys[fa].head, polys[fb].head);
    poly.name = ch;
    if(fch >= 0) {
        polys[fch] = poly;
        *idx = fch;
        printf("%c=", ch);
        printPoly(poly);
    } else {
        printf("%c+%c=", ca, cb);
        printPoly(poly);
        clearPoly(&poly.head);
    }
}

void minusPolyExp(Poly* polys, int *idx, char *input) {
    char *iptr = input;
    char ch, ca, cb;
    int fch, fa, fb; //flags
    fch = fa = fb = -1; // -1 = not found
    
    // check if first char. is alphabet 
    ch = *iptr;
    if(!isalpha(ch)) {
        *idx = -1;
        return;
    }
    
    iptr++;
    if(*iptr == '-') {
        ca = ch;
        cb = *++iptr;
        ch = 0;
        fch = -2; // don't seek
    } else if(*iptr == '=') {
        ca = *++iptr;
        if(*++iptr != '-') {
            *idx = -1;
            return;
        }
        cb = *++iptr;
    } else {
        *idx = -1;
        return;
    }

    for(*idx=0; *idx<MAX_POLYS; (*idx)++) {
        if(polys[*idx].head == NULL) {
            if(fch == -1)
                fch = *idx;
            break;
        }
        if(polys[*idx].name == ch) {
            fch = *idx;
        }
        if(polys[*idx].name == ca) {
            fa = *idx;
        }
        if(polys[*idx].name == cb) {
            fb = *idx;
        }
        
        if((fa!=-1 && fb!=-1) && fch!=-1) {
            break;
        }

        if(*idx == MAX_POLYS-1) {
            *idx = -2;
            return;
        }
    }

    if(fa==-1 || fb==-1) {
        *idx = -1;
        return;
    }
    
    Poly poly;
    poly.head = minusPoly(polys[fa].head, polys[fb].head);
    poly.name = ch;
    if(fch >= 0) {
        polys[fch] = poly;
        *idx = fch;
        printf("%c=", ch);
        printPoly(poly);
    } else {
        printf("%c-%c=", ca, cb);
        printPoly(poly);
        clearPoly(&poly.head);
    }
}

int main() {
    int polyCount = 0;
    Poly *polys = (Poly*) malloc( sizeof(Poly) * MAX_POLYS );
    for(int i=0; i<MAX_POLYS; i++) {
        polys[i].head = NULL; // init
        polys[i].name = 0;
    }
    
    int cmd;
    char input[100];
    while (scanf("%d", &cmd)) {
        if(cmd == 0) {
            break;
        }
        if(cmd == 1) {
            int idx;
            scanf("%s", input);
            readPoly(polys, &idx, input);
            if(idx < 0) {
                if(idx == -1)
                    printf("ERROR\n");
                if(idx == -2)
                    printf("FULL\n");
                continue;
            }
            printf("%c\n", polys[idx].name);
            printPair(polys[idx].head);
        }
        if(cmd == 2) {
            scanf("%s", input);
            for(int i=0; i<MAX_POLYS; i++) {
                if(polys[i].name == input[0]) {
                    printf("%c=", polys[i].name);
                    printPoly(polys[i]);
                    break;
                }
                if(i == MAX_POLYS-1) {
                    printf("NO POLY\n");
                }
            }
        }
        if(cmd == 3) {
            printAllPolys(polys);
        }
        if(cmd == 4) {
            int idx;
            scanf("%s", input);
            addPolyExp(polys, &idx, input);
            if(idx < 0) {
                if(idx == -1)
                    printf("ERROR\n");
                if(idx == -2)
                    printf("FULL\n");
                continue;
            }
        }
        if(cmd == 5) {
            int idx;
            scanf("%s", input);
            minusPolyExp(polys, &idx, input);
            if(idx < 0) {
                if(idx == -1)
                    printf("ERROR\n");
                if(idx == -2)
                    printf("FULL\n");
                continue;
            }
        }

    }
    printf("quit\n");


    return 0;
}
