#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 1000
#define MAX_CHARS 10000+1

void inputTree(int *tree, int *size) {
    char *input = (char*) malloc(sizeof(char) * MAX_CHARS);
    for (int n=1; n<MAX_NODES; n<<=1) {
        fgets(input, MAX_CHARS, stdin);
        char *tmp = strtok(input, " \n");
        for (int i=0; i<n; i++) {
            if (tmp[0] == 'e') {
                *size = n-1; 
                printf("OK\n");
                return;
            }
            if (tmp[0] == 'x') {
                tree[n-1+i] = -1;
            } else {
                tree[n-1+i] = atoi(tmp);
            }
            tmp = strtok(NULL, " \n");
        }
    }
    printf("MAX NODES REACHED");
}

void printTree(int *tree, int size) {
    for (int n=1; n<=size; n<<=1) {
        for (int i=0; i<n; i++) {
            printf("%d ", tree[n-1+i]);
        }
        printf("\n");
    }
}

int main() {

    int *tree = (int*) malloc(sizeof(int) * MAX_NODES);
    int size;

    inputTree(tree, &size);
    printTree(tree, size);

    return 0;
}

/*
14
12 7
10 8 6 x 

0         < 1 (1-1)
1 2       < 2 (2-1)
3 4 5 6   < 4 (4-1+i)
*/