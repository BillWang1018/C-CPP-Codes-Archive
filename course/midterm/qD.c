#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_POLYS 10

typedef struct EqNode {
    int coe;
    char var;
    int exp;
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

EqNodePtr clearEqNodes(EqNodePtr *node) {
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

void pushEqNode(EqNodePtr *node, int coe, char var, int exp) {
    if(coe == 0) return;

    EqNodePtr nptr = *node;
    EqNodePtr newNode = (EqNodePtr) malloc( sizeof(EqNode) );
    newNode->coe = coe;
    newNode->var = var;
    newNode->exp = exp;
    newNode->next = NULL;

    if(!nptr) {
        *node = newNode;
        // printf("BREAKPOINT1 %p\n", node);
        return;
    }

    while(nptr->next) {
        nptr = nptr->next;
    }
    nptr->next = newNode;
}

int readEq(EqPtr *eqs, char *input) {
    EqNodePtr eq = (EqNodePtr) malloc(sizeof(EqNode));
    int prevExp;
    int termCount;
    char *iptr = input;
    char name, prev, next, num[15], *nump, var, prevVar;

    eq = NULL;
    prevExp=2147483647, termCount=0, prevVar=0;

    name = *iptr;
    if(!isalpha(name)) {
        return -1;
    }
    
    prev = *iptr++;
    next = *iptr;

    if(next != '=') {
        return -1;
    }
    prev = *iptr++;
    next = *iptr;

    if(next == '\0') {
        return -1;
    }
    /* PROCESS equation */
    int coe=0;
    int exp=0;

    while(next != '\0') {
        termCount++;

        /* PROCESS coefficient */
        nump = num;
        while(1) {
            if(next == '\0') {
                *nump = '\0';
                coe = atoi(num);
                break;
            }
            else if(isalpha(tolower(next))) {
                // check if term is -x or +x or x (coe. is 1 or -1)
                var = tolower(next);
                if(prev == '+' || prev == '=') {
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
                free(eq);
                return -1;
            }
        }

        if(coe == 0) { // coe. can't be 0
            clearEqNodes(&eq);
            free(eq);
            return -1;
        }
        
        if(next != '\0') {
            prev = *iptr++;
            next = *iptr;
        }

        /* PROCESS exponent */
        // is constant
        if(next == '\0' && tolower(prev) != 'x') {
            var = exp = 0;
        }
        else if(next == '^') {
            prev = *iptr++;
            next = *iptr;
            nump = num;
            while(1) {
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
                    clearEqNodes(&eq);
                    free(eq);
                    return -1;
                }
            }
        }
        else if(next == '\0' || (next == '+' || next == '-')) {
            exp = 1;
        }
        else if(!isdigit(next)) {
            clearEqNodes(&eq);
            free(eq);
            return -1;
        }

        if(prevExp < exp || (prevExp == exp && prevVar == var)) {
            clearEqNodes(&eq);
            free(eq);
            return -1;
        }
        prevExp = exp;
        prevVar = var;
        // store data
        pushEqNode(&eq, coe, var, exp);
    }
    // push to eqs
    EqPtr tmp = *eqs;
    if(tmp) {
        while(tmp) {
            // record tmp if found
            if(tmp->name == name) break;
            // move tmp to NULL if not found
            tmp = tmp->next;
        }
    }
    if(tmp) { // found
        clearEqNodes(&tmp->head);
        tmp->head = eq;
        tmp->size = termCount;
    } else { // not found
        pushEq(eqs, termCount, name, eq);
    }
    return name; // sucess
}

void printData(EqPtr eq) {
    EqNodePtr nptr = eq->head;
    printf("%c %d\n", eq->name, eq->size);
    while(nptr != NULL) {
        printf("%d %d", nptr->coe, nptr->exp);
        if(nptr->var) {
            printf(" %c", nptr->var);
        }
        printf("\n");
        nptr = nptr->next;
    }
}

void printEq(EqNodePtr head) {
    int coe, exp;
    char var;
    EqNodePtr nptr = head;
    while(nptr != NULL) {
        coe = nptr->coe;
        exp = nptr->exp;
        var = nptr->var;
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
            printf("%c", var);
        } 
        else {
            printf("%c^%d", var, exp);
        }

        nptr = nptr->next;
    }
    printf("\n");
}

void printAllEqs(EqPtr eqs) {
    if(eqs == NULL) {
        printf("NO EQUATION\n");
        return;
    }
    EqPtr tmp = eqs;
    while(tmp) {
        printf("%c=", tmp->name);
        printEq(tmp->head);
        tmp = tmp->next;
    }
}

EqNodePtr addEqs(EqNodePtr eqA, EqNodePtr eqB) {
    EqNodePtr a = eqA, b = eqB;
    EqNodePtr sum = NULL;
    while(a || b) {
        if(a && !b) { // only A
            pushEqNode(&sum, a->coe, a->var, a->exp);
            a = a->next;
            continue;
        }
        if(!a && b) { // only B
            pushEqNode(&sum, b->coe, b->var, b->exp);
            b = b->next;
            continue;
        }

        if(a->exp > b->exp) {
            pushEqNode(&sum, a->coe, a->var, a->exp);
            a = a->next;
            continue;
        }
        if(b->exp > a->exp) {
            pushEqNode(&sum, b->coe, b->var, b->exp);
            b = b->next;
            continue;
        }
        if(a->exp == b->exp) {
            if(a->var == b->var) {
                pushEqNode(&sum, a->coe + b->coe, a->var, a->exp);
                a = a->next;
                b = b->next;
            } 
            else if(a->var < b->var) {
                pushEqNode(&sum, a->coe, a->var, a->exp);
                a = a->next;
            }
            else if(b->var < a->var) {
                pushEqNode(&sum, b->coe, b->var, b->exp);
                b = b->next;
            }
        }
        
    }
    return sum;
}

void addEqsIO(EqPtr *eqs, char *input) {
    int mode;
    if(input[1] == '=' && input[3] == '+')
        mode = 0;
    else if(input[1] == '+')
        mode = 1;
    else {
        printf("addIO ERR\n");
        return;
    }

    char des, ca, cb;
    EqPtr ed, ea, eb, tmp;
    ed = ea = eb = NULL;
    tmp = *eqs;
    if(mode == 0) {
        des = input[0];
        ca  = input[2];
        cb  = input[4];
        while(tmp) {
            if(tmp->name == des)
                ed = tmp;
            if(tmp->name == ca)
                ea = tmp;
            if(tmp->name == cb)
                eb = tmp;
            tmp = tmp->next;
        }
        //check if all are found
        if(!ea || !eb) {// any of a or b is null
            if(!ea)
                printf("NO EQUATION %c\n", ca);
            if(!eb)
                printf("NO EQUATION %c\n", cb);
            return;
        }
        EqNodePtr sum = addEqs(ea->head, eb->head), tmpsum;
        tmpsum = sum;
        int cnt=0;
        while(tmpsum) {
            cnt++;
            tmpsum = tmpsum->next;
        }
        if(ed == NULL) { // not found, push a new node
            pushEq(eqs, cnt, des, sum);
            printf("%c=", des);
            printEq(tmp->head);
        }
    }
    if(mode == 1) {
        des = 0;
        ca  = input[0];
        cb  = input[2];
        while(tmp) {
            if(tmp->name == ca)
                ea = tmp;
            if(tmp->name == cb)
                eb = tmp;
            tmp = tmp->next;
        }
        //check if all are found
        if(!ea || !eb) {// any of a or b is null
            if(!ea)
                printf("NO EQUATION %c\n", ca);
            if(!eb)
                printf("NO EQUATION %c\n", cb);
            return;
        }
        EqNodePtr sum = addEqs(ea->head, eb->head);
        printf("%c+%c=", ca, cb);
        printEq(sum);
    }
}

int main() {
    int eqCount = 0;
    EqPtr eqs = (EqPtr) malloc(sizeof(Eq)), tmp;
    eqs = NULL;

    int cmd;
    char input[100];
    while (scanf("%d", &cmd)) {
        if(cmd == 0) {
            break;
        }
        if(cmd == 1) {
            scanf("%s", input);
            int idx = readEq(&eqs, input);
            if(idx < 0) {
                if(idx <= -1)
                    printf("ERROR\n");
                continue;
            } else {
                tmp = eqs;
                while(tmp->name != idx) {
                    tmp = tmp->next;
                }
                printData(tmp);
            }
        }
        if(cmd == 2) {
            scanf("%s", input);
            tmp = eqs;
            while(tmp->name != *input && tmp->next) {
                tmp = tmp->next;
            }
            if(tmp->name != *input) {
                printf("NO EQUATION\n");
            } else {
                printf("%c=", *input);
                printEq(tmp->head);
            }
        }
        if(cmd == 3) {
            printAllEqs(eqs);
        }
        if(cmd == 4) {
            scanf("%s", input);
            addEqsIO(&eqs, input);
        }

    }
    printf("quit\n");

    return 0;
}
