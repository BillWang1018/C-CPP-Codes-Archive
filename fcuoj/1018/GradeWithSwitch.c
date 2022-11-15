#include <stdio.h>
int main() {
    int value;
    char grade;
    scanf("%d", &value);
    switch (value) {
        case 01 ... 59:
            grade = 'E';
            break;
        case 60 ... 69:
            grade = 'D';
            break;
        case 70 ... 79:
            grade = 'C';
            break;
        case 80 ... 89:
            grade = 'B';
            break;
        case 90 ... 100:
            grade = 'A';
            break;
    }
    printf("%c", grade);
}