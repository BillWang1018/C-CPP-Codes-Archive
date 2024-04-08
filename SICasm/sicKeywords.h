#ifndef SIC_KEYWORDS
#define SIC_KEYWORDS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// ### Return 0x0opf or -1 ###
// op (2 bytes) for opcode, f (1 byte, 1-3) for format 1,2,3/4
// If not found, return -1
int getopInfo(char *str) {
    // convert to upper case
    int i;
    char op[10];
    for(i=0; i<10 && str[i]; i++) {
        op[i] = toupper(str[i]);
    }
    op[i] = '\0';
    // read instruction tables
    FILE *fptr;
    
    if((fptr = fopen("instructionTable.csv","r")) == NULL) {
        printf("error reading op table!\n");
        exit(1);
    }
    // test if included
    bool flag;
    char buf[20], *tok;
    while(fscanf(fptr,"%s",buf) != EOF) {
        flag = true;
        tok = strtok(buf, ",");
        // skip if different length
        if (strlen(op) != strlen(tok)) {
            continue;
        }

        for(int i=0; tok[i]; i++) {
            if(tok[i] != op[i]) {
                flag = false; break;
            }
        }
        // if keyword is found
        if (flag) {
            int format=0,opcode=0;
            tok = strtok(NULL, ",");
            if (*tok == 'A') format=1;
            if (*tok == 'B') format=2;
            if (*tok == 'C') format=3;
            tok = strtok(NULL, ",");
            opcode = (int) strtol(tok, &tok, 16);
            fclose(fptr);
            return (opcode << 4) + format;
        } else continue;
    }

    fclose(fptr);
    return -1;
}

#endif