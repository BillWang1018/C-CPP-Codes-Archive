#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int n=0;
    char *str;
    str = (char*) malloc(30 * sizeof(char));
    while(1) {
        scanf("%s", str);
        //printf("-- %s\n", str);
        if(!strcmp(str, "#")) break;
        n++;
        printf("Case %d: ", n);
        if(!strcmp(str, "HELLO")) printf("ENGLISH");
        else if(!strcmp(str, "HOLA")) printf("SPANISH");
        else if(!strcmp(str, "HALLO")) printf("GERMAN");
        else if(!strcmp(str, "BONJOUR")) printf("FRANCH");
        else if(!strcmp(str, "CIAO")) printf("ITALIAN");
        else if(!strcmp(str, "ZDRAVSTVUJTE")) printf("RUSSIAN");
        else printf("UNKNOWN");
        printf("\n");
    }
}