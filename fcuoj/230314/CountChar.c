#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* count_chars(char *str) {
    int *counter;
    char *c;
    counter = (int*)malloc(26 * sizeof(int));
    for(int i=0; i<26; i++) 
        *(counter+i) = 0;

    c = str;
    while(*c != '\0') {
        *c = tolower(*c);
        if(*c >= 'a' && *c <= 'z')
            *(counter+(*c-'a')) += 1;
        c++;
    }
    
    return counter;
}

int main() {
    size_t maxsize = 200;
    char *str;
    str = (char*)malloc(maxsize * sizeof(char));
    int* (*count) (char*);
    count = count_chars;

    // getline(&str, &maxsize, stdin);
    fgets(str, maxsize, stdin);

    int *counter = (*count)(str);

    for(int i='a'; i<='z'; i++) 
        printf("%c: %d%s", i, *(counter+(i-'a')), ((i=='z') ? "" : "\n" ));
    return 0;
}