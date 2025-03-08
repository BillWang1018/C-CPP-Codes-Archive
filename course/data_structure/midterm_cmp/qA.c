#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct EqNode {
    int *coe;
    int *exp;
    // char var;
    // [0]->x, [1]->y, [2]->z, [3]->const #ascii: {
    struct EqNode *next;
} EqNode;

typedef struct Eq {
    int size;
    char name;
    struct EqNode *head;
    struct Eq *next;
} Eq;

typedef EqNode * EqNodePtr;
typedef Eq * EqPtr;

int max(int a, int b) {
    return a>b ? a : b;
}

EqNodePtr clearEqNodes(EqNodePtr *node) {
    if(!(*node)) return NULL;
    EqNodePtr nptr = *node;
    while(nptr->next) {
        nptr = nptr->next;
        free(*node);
        *node = nptr;
    }
    free(*node);
    *node = NULL;
}

void pushEq(EqPtr *node, int size, char name, EqNodePtr head) {
    EqPtr nptr = *node;
    EqPtr newNode = (EqPtr) malloc(sizeof(Eq));
    newNode->name = name;
    newNode->size = size;
    newNode->next = NULL;
    newNode->head = head;

    if(!*node) {
        *node = newNode;
        return;
    }

    while(nptr->next) {
        nptr = nptr->next;
    }
    nptr->next = newNode;
}

void pushEqNode(EqNodePtr *node, int *coe, int *exp) {
    EqNodePtr nptr = *node;
    EqNodePtr newNode = (EqNodePtr) malloc( sizeof(EqNode) );
    newNode->coe = coe;
    newNode->exp = exp;
    newNode->next = NULL;

    if(!nptr) {
        *node = newNode;
        return;
    }

    while(nptr->next) { 
        nptr = nptr->next;
    }
    nptr->next = newNode;
}

void printNodeData(EqNodePtr node) {
    EqNodePtr nptr = node;
    while(nptr != NULL) { 
        for(int var=0; var<4; var++) {
            // printf("%d | %d %d\n", var, nptr->coe[var], nptr->exp[var]);
            if(!nptr->coe[var]) continue;
            if(var == 3) {
                printf("%d 0\n", nptr->coe[var]);
                continue;
            }
            printf("%d %c %d\n", 
                    nptr->coe[var], 
                    var+'x',
                    nptr->exp[var]
            );
        }
        nptr = nptr->next;
    }
}

void readEq(EqPtr *eqs, char *input) {
    EqNodePtr eq = (EqNodePtr) malloc(sizeof(EqNode));
    int prevExp;
    int termCount;
    char *iptr = input;
    char name, prev, next, num[15], *nump, var, prevVar;

    eq = NULL;
    prevExp=2147483647, termCount=0, prevVar=0;

    prev = '=';
    next = *iptr;
    int coeArr[4]={0}, expArr[4]={0};
    /* PROCESS term */
    int coe=0;
    int exp=0;

    while(next != '\0') {
        // termCount++;

        /* PROCESS coefficient */
        nump = num;
        while(1) {
            // printf("%c\n", next);
            if(next == '\0') {
                *nump = '\0';
                coe = atoi(num);
                break;
            }
            else if(isalpha(tolower(next))) {
                // check if term is -x or +x or x (coe. is 1 or -1)
                var = tolower(next);
                if(prev == '+' || prev == '=' || prev == '*') {
                    coe = 1;
                    break;
                }
                else if( prev == '-' ) {
                    coe = -1;
                    break;
                }
                else {
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
                clearEqNodes(&eq);
                printf("ERROR\n");
                return;
                // return -1;
            }
        }

        if(coe == 0) { // coe. can't be 0
            clearEqNodes(&eq);
            return;
            // return -1;
        }
        
        if(next != '\0') {
            prev = *iptr++;
            next = *iptr;
        }


        /* PROCESS exponent */
        // is constant
        if(next == '\0' && !isalpha(prev)) {
            exp = 0;
            var = '{'; // next ascii of 'z'
        }
        else if(next == '^') {
            prev = *iptr++;
            next = *iptr;
            nump = num;
            while(1) {
                if(next == '\0' || (next == '+' || next == '-') || next == '*') {
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
                    clearEqNodes(&eq);
                    printf("ERROR\n");
                    return;
                    // return -1;
                }
            }
        }
        else if(next == '\0' || (next == '+' || next == '-') || next == '*') {
            exp = 1;
        } 
        else {
            clearEqNodes(&eq);
            printf("ERROR\n");
            return;
            // return -1;
        }
        
        coeArr[var-'x'] = coe;
        expArr[var-'x'] = exp;
        prevExp = max(exp, prevExp);
        if(next ==  '*') {
            prev = *iptr++;
            next = *iptr;
        }
    }
    // store data
    pushEqNode(&eq, coeArr, expArr);

    printNodeData(eq);

}

int main() {
    int eqCount = 0;
    EqPtr eqs = (EqPtr) malloc(sizeof(Eq)), tmp;
    eqs = NULL;

    int cmd;
    char input[100];

    while(scanf("%s", input) != EOF) {
        if(*input == '0') break;
        readEq(&eqs, input);
    }
    printf("quit\n");

    return 0;
}
