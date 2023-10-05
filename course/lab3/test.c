#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
    char str[] = "123x^456+12x^45";
    char *ptr = str, *ptr1;
    printf("%s\n", ptr);
    ptr = strtok(str, "^");
    printf("%s\n", ptr);
    ptr1 = strtok(ptr, "x");
    printf("%s\n", ptr);

    printf("%f", atof("+1.23"));

}