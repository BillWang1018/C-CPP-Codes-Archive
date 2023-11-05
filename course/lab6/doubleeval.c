#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CHAR 100

typedef struct {
    int top;
    char *stack;
} CharStack;

typedef struct {
    int top;
    double *stack;
} DoubleStack;

CharStack *newCharStack() {
    CharStack *stack = (CharStack*)malloc(sizeof(CharStack));
    if(!stack) {
        free(stack);
        return 0;
    }
    stack->top = 0;
    stack->stack = (char*)malloc(sizeof(char) * MAX_CHAR);
    if(!stack->stack) {
        free(stack);
        return 0;
    }
    return stack;
}

DoubleStack *newDoubleStack() {
    
    DoubleStack *stack = (DoubleStack*)malloc(sizeof(DoubleStack));
    if(!stack) {
        free(stack);
        return 0;
    }
    stack->top = 0;
    stack->stack = (double*)malloc(sizeof(double) * MAX_CHAR);
    if(!stack->stack) {
        free(stack);
        return 0;
    }
    return stack;
}

void pushC(CharStack *st, char c) {
    if(st->top < MAX_CHAR-1)
        st->stack[st->top++] = c;
}
void pushD(DoubleStack *st, int c) {
    if(st->top < MAX_CHAR-1)
        st->stack[st->top++] = c;
}

char *popC(CharStack *st) {
    return &st->stack[--st->top];
}
double popD(DoubleStack *st) {
    return st->stack[--st->top];
}

char topC(CharStack *st) {
    return st->stack[st->top-1];
}
double topD(DoubleStack *st) {
    return st->stack[st->top-1];
}

int precedence(char c) {
    if(c == '(') return 0;
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    if(c == '^') return 3;

    return -1;
}

void voidintoPostfix(char *str, char *post) {
    // post = (char*) malloc(sizeof(char) * MAX_CHAR);
    strcpy(post, "");
    int flag = 1;
    char *c = str, latest = *c;
    CharStack *s = newCharStack();
    while(*c != '\0') {
        // printf("s.top = %d | post = %s\n", s->top, post);
        // printf("s.top = %d | post = %s\n", s->top, post);
        if(isalnum(*c)) {
            if(isalnum(latest) && *c != *str) {
                flag = 0;
                break;
            }
            strncat(post, c, 1);
        } else if(*c == '(') {
            pushC(s, *c);
        } else if(*c == ')') {
            while(s->top && topC(s)!='(') {
                strncat(post, popC(s), 1);
            }
            if(topC(s) != '(') {
                flag = 0;
                break;
            } else {
                popC(s);
            }
        } else if(precedence(*c) < 0) {
            flag = 0;
            break;
        } else {
            if(!isalnum(latest) && *c != *str && precedence(latest) > 0) {
                flag = 0;
                break;
            }
            while(s->top && precedence(topC(s)) >= precedence(*c)) {
                strncat(post, popC(s), 1);
            }
            pushC(s, *c);
        }
        latest = *(c++);
    }
    if(!flag) {
        strcpy(post, "ERROR");
        return;
    }
    while(s->top) {
        strncat(post, popC(s), 1);
    }
} 

void voidgetValue(char *infix, int *vals) {
    char *postfix = (char*) malloc(sizeof(char) * MAX_CHAR);
    voidintoPostfix(infix, postfix);
    printf("Infix:%s\nPostfix:%s\n", infix, postfix);
    if(!strcmp(postfix, "ERROR")) {
        return;
    }
    int *isEmpty = (int*) malloc(sizeof(int) * 255);
    memset(vals, 0, 255);
    memset(isEmpty, 1, 255);
    for(char *c=infix; *c != '\0'; c++) {
        if(isalpha(*c) && isEmpty) {
            printf("%c:", *c);
            scanf("%d", &vals[*c]);
            isEmpty[*c] = 0;
        }
    }
    DoubleStack *s = newDoubleStack();
    for(char *c=postfix; *c != '\0'; c++) {
        if(isalpha(*c)) {
            pushD(s, vals[*c]);
        }
        if(isdigit(*c)) {
            pushD(s, *c-'0');
        }

        double a,b;
        if(*c == '+') {
            a=b=0;
            if(s->top)
                a = popD(s);
            if(c-2 >= postfix)
                b = popD(s);
            pushD(s, a+b);
        }
        if(*c == '-') {
            a=b=0;
            if(s->top)
                a = popD(s);
            if(c-2 >= postfix)
                b = popD(s);
            pushD(s, b-a);
        }
        if(*c == '*') {
            a=b=0;
            if(s->top)
                a = popD(s);
            if(s->top)
                b = popD(s);
            pushD(s, a*b);
        }
        if(*c == '/') {
            a=b=0;
            if(s->top)
                a = popD(s);
            if(s->top)
                b = popD(s);
            pushD(s, a/b);
        }
        if(*c == '^') {
            a=b=0;
            if(s->top)
                a = popD(s);
            if(s->top)
                b = popD(s);
            pushD(s, pow(b, a));
        }
    }
    if(s->top) {
        printf("%.1lf\n", popD(s));
    } else {
        printf("Error evaling\n");
    }
}

int main() {
    char *str  = (char*) malloc(sizeof(char) * MAX_CHAR);
    char *post = (char*) malloc(sizeof(char) * MAX_CHAR);
    int  *vals = (int*) malloc(sizeof(int) * 255);
    // int skipLines = 1;
    while(scanf("%s", str) != EOF) {
        // printf(skipLines-- > 0 ? "" : "");
        voidintoPostfix(str, post);
        printf("%s%s\n\n", (strcmp(post, "ERROR") ? "Postfix expression:" : "") , post);
        voidgetValue(str, vals);
    }
    return 0;
}