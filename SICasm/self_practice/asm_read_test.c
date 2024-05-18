#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *file;
    char *line;
    size_t len=0;
    fopen(".\\ObjectCodeExample\\Figure39_137_PROGA.txt", "r");
    if (file == NULL) {
        printf("Unable to read file\n");
    }
    getline(&line, &len, file);
    fclose(file);
    return 0;
}