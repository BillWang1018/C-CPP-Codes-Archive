#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_NUMS 1005
#define MAX_CHARS 10005

void inputArr(int *arr, int *size) {
    char *input = (char*) malloc(sizeof(char) * MAX_CHARS);
    fgets(input, MAX_CHARS, stdin);
    char *tmp = strtok(input, " \n");
    for (int i=0; i<MAX_NUMS; i++) {
        if (tmp == NULL) {
            *size = i;
            return;
        }
        arr[i] = atoi(tmp);
        tmp = strtok(NULL, " \n");
    }
}

void sort(int *arr, int *dest, int size) {
    int max=0;
    bool bucket[MAX_NUMS];
    memset(bucket, false, sizeof(bucket));
    for (int i=0; i<size; i++) {
        bucket[arr[i]] = true;
        max = (max > arr[i]) ? max : arr[i];
    }
    for (int i=0, j=0; i<=max; i++) {
        if (bucket[i])
            dest[j++] = i;
    }
}

int minOrder(int *arr, int size, int order) {
    int *sorted = (int*) malloc(sizeof(int) * size);
    sort(arr, sorted, size);
    return sorted[order-1];
}

void printArr(int *arr, int size) {
    for (int i=0; i<size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *arr = (int*) malloc(sizeof(int) * MAX_NUMS);
    int size=0;

    char *input = (char*) malloc(sizeof(char) * MAX_CHARS);
    while (fgets(input, MAX_CHARS, stdin)) {
        switch (input[0]) {
            case 'i':
                inputArr(arr, &size);
                break;
            case 'p':
                printArr(arr, size);
                break;
            case 'f':;
                int order = atoi(input+1);
                if (order > size) 
                    printf("NULL\n");
                else
                    printf("%d\n", minOrder(arr, size, order));
                break;
            case '0':
                printf("quit\n");
                return 0;
        }
    }

    return 0;
}

/* test case

i
1 2 3 4 5 6 7 8





*/