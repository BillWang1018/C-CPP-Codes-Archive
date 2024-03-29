#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CHAR 100

typedef struct LogicTree {
    char ch;
    struct LogicTree* r, *l;
} Tree;

Tree* newNode(char ch) {
    Tree* newNode = (Tree*) malloc(sizeof(Tree));
    newNode->ch = ch;
    newNode->r = newNode->l = NULL;
    return newNode;
}

Tree* stackTree[MAX_CHAR];
int lastsTree=0;

void pushTree(Tree* element) {
    stackTree[lastsTree++] = element;
}

Tree* popTree() {
    if (lastsTree) {
        return stackTree[--lastsTree];
    } else {
        return NULL;
    }
}

Tree* topTree() {
    if (lastsTree) {
        return stackTree[lastsTree-1];
    } else {
        return NULL;
    }
}

char stackChar[MAX_CHAR];
int lastsChar=0;

void pushChar(char c) {
    stackChar[lastsChar++] = c;
}

char popChar() {
    if (lastsChar) {
        return stackChar[--lastsChar];
    } else {
        return 0;
    }
}

char topChar() {
    if (lastsChar) {
        return stackChar[lastsChar-1];
    } else {
        return 0;
    }
}


Tree* makeTree(char* str) {
    int p[255] = {0};
    p['('] = 1;
    p['^'] = p['v'] = 2;
    p['-'] = 3;
    lastsChar = lastsTree = 0;
    char op;

    for (char* c = str; *c != '\0'; c++) {
        // is variable
        if (isalpha(*c) && !p[*c]) {
            pushTree(newNode(*c));
        } // is (
        else if (*c == '(') {
            pushChar(*c);
        } // is ) 
        else if (*c == ')') {
            while (op = popChar()) {
                if (op == '(') break;
                Tree *new = newNode(op);
                new->r = popTree();
                new->l = popTree();
                pushTree(new);
            }
        } // is operator 
        else {
            // is illegal operator
            if (p[*c] == 0) {
                return NULL;
            }
            bool unary = false;
            // is unary operator
            if (*c == '-' && (c == str ||  p[*(c-1)] )) {
                unary = true;
            }
            // add to stack or pop
            while (op = topChar()) {
                if (p[op] < p[*c]) break;
                Tree* new = newNode(op);
                new->r = popTree();
                new->l = popTree();
                pushTree(new);
                popChar();
            }

            if(unary) pushTree(NULL);
            pushChar(*c);
        }
    }

    // clear remaining stack
    while (op = popChar()) {
        Tree* new = newNode(op);
        new->r = popTree();
        new->l = popTree();
        pushTree(new);
    }
    
    return topTree();
}

int height(Tree* head) {
    if (!head)
        return 0;
    int lheight = height(head->l);
    int rheight = height(head->r);
    // use the larger one
    return (lheight > rheight) ? lheight+1 : rheight+1;
}
void printCurrentLevel(Tree* head, int level) {
    if (!head)
        return;
    if (level == 1)
        printf("%c", head->ch);
    else if (level > 1) {
        printCurrentLevel(head->l, level-1);
        printCurrentLevel(head->r, level-1);
    }
}
void printTreeLevelOrder(Tree* head) {
    for (int i=1; i <= height(head); i++)
        printCurrentLevel(head, i);
}

void printTreePreOrder(Tree* head) {
    if(!head) return;
    printf("%c", head->ch);
    printTreePreOrder(head->l);
    printTreePreOrder(head->r);
}
void printTreePostOrder(Tree* head) {
    if(!head) return;
    printTreePostOrder(head->l);
    printTreePostOrder(head->r);
    printf("%c", head->ch);
}

int main() {
    char str[MAX_CHAR];
    while(scanf("%s", str)) {
        
        if(*str == '0') break;
        Tree* tree = makeTree(str);
        printTreeLevelOrder(tree);
        // printTreePreOrder(tree);
        // printTreePostOrder(tree);
        printf("\n");
    }
    printf("quit");
    return 0;
}