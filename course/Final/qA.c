#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 1005
#define MAX_CHARS 10005

void inputTree(char *tree, int *size) {
    char *input = (char*) malloc(sizeof(char) * MAX_CHARS);
    for (int n=1; n<MAX_NODES; n<<=1) {
        fgets(input, MAX_CHARS, stdin);
        char *tmp = strtok(input, " \n");
        for (int i=0; i<n; i++) {
            if (!strcmp(tmp, "end")) {
                *size = n-1; 
                printf("OK\n");
                return;
            }
            if (!strcmp(tmp, "99")) {
                tree[n-1+i] = 0;
            } else {
                tree[n-1+i] = tmp[0];
            }
            tmp = strtok(NULL, " \n");
        }
    }
    printf("MAX NODES REACHED\n");
}

void printTree(char *tree, int size) {
    for (int n=1; n<=size; n<<=1) {
        for (int i=0; i<n; i++) {
            printf("%c ", tree[n-1+i]);
        }
        printf("\n");
    }
}

bool findPathExists(char *tree, int size, char *path, int i) {
    // printf("COMP: %c | %c\n", *path, tree[i]);
    if (*path == '\n') return true;
    if (i >= size) return false;
    if (tree[i] == *path) {
        return  findPathExists(tree, size, path+1, i*2+1) || 
                findPathExists(tree, size, path+1, i*2+2);
    } else {
        return false;
    }

}

int main() {

    char *tree = (char*) malloc(sizeof(char) * MAX_NODES);
    int size=0;

    char *input = (char*) malloc(sizeof(char) * MAX_CHARS);
    while (fgets(input, MAX_CHARS, stdin)) {
        switch (input[0]) {
            case '1':
                inputTree(tree, &size);
                break;
            case '2':
                if (size) {
                    fgets(input, MAX_CHARS, stdin);
                    printf("%s\n", findPathExists(tree, size, input, 0) ? "YES" : "NO");
                }
                else {
                    printf("NULL\n");
                }
                break;
            case 'p':
                printTree(tree, size);
                break;
            case '0':
                printf("quit\n");
                return 0;
        }
    }
    return 0;
}
/* test case



1
a
b c
d e f 99
end
2
abd
2
abc

===========================================

1
x
y z
w 99 m n
99 99 99 99 p 99 99 99
end
2
xyz
2 
xyw
2
ywz
0


*/