#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYM 100

// functions and varables for Table
typedef struct Table {
    char key[10];
    int value, type; // type 1 = CS, type 2 = Symbol
    int secLen;
} Table;

int _establen_ = 0;
Table estab[MAX_SYM];

// push a key, value pair into Table //
void pushTable(char *key, int value, int type) {
    if (_establen_ >= MAX_SYM) return;
    strcpy(estab[_establen_].key, key);
    estab[_establen_].value = value;
    estab[_establen_].type = type;
    _establen_++;
}

void addCSLenToTable(char *key, int secLen) {
    for (int i=0; i<_establen_; i++) {
        if (estab[i].type == 1 && !strcmp(estab[i].key, key)) {
            estab[i].secLen = secLen;
        }
    }
}

// find value with key in Table, NULL returns -1
int findTable(char *key) {
    for (int i=0; i<_establen_; i++) {
        if (!strcmp(estab[i].key, key)) {
            return estab[i].value;
        }
    }
    return -1;
}

void printTable() {
    printf("List of ESTAB:\n");
    printf("%33s\n", "---------------------------------");
    printf("%-6s | %-6s | %-6s | %-6s\n", "CS", "SYMBOL", "ADDR", "CS_LEN");
    printf("%33s\n", "---------------------------------");
    for (int i=0; i<_establen_; i++) {
        if (estab[i].type == 1)
            printf("%-6s | %-6s | %06X | %06X\n", estab[i].key, "", estab[i].value, estab[i].secLen);
        if (estab[i].type == 2)
            printf("%-6s | %-6s | %06X | %6s \n", "", estab[i].key, estab[i].value, "x");
    }
    printf("%33s\n", "---------------------------------");
}

// end Table //

int main(int argc, char *argv[]) {
    FILE *file;
    char line[128], csName[10], subStr[10], symName[10];
    int curfile, csAddr, csOffset, csLen, lineCnt, symAddr;

    // terminate if wrong usage
    // not enought args
    if (argc < 2) {
        printf("Usage: asm_loader_pass1 <address> <obj_file0> <obj_file1>...");
        return 0;
    }
    // start addr not a hex number
    for (int i=0; i<strlen(argv[1]); i++) {
        // test if digit 0-F
        char c=toupper(argv[1][i]);
        if (!isdigit(c) && !(c >= 'A' && c <= 'F')) {
            printf("Use Hex number as address: asm_loader.exe <address> <obj_file0> <obj_file1>...");
            return 0;
        }
    }

    // read in hex number as start
    sscanf(argv[1], "%6x", &csAddr);
    printf("Program Address Starts at %X...\n", csAddr);
    curfile = 1;

    // continue reading all files 
    while (++curfile < argc) {
        // open file
        file = fopen(argv[curfile], "r");
        if (file == NULL) {
            printf("Unable to read file: %s\n", argv[curfile]);
            continue;
        }
        // printf("Process File: %s\n", argv[curfile]);
        // read each line
        lineCnt=0;
        while (fgets(line, sizeof(line), file)) {
            lineCnt++;
            // printf("Process Line %2d | %s", lineCnt, line);
            // check Header record //
            if (lineCnt == 1) {
                if (line[0] == 'H') {
                    // read CS name
                    strncpy(subStr, &line[1], 6);
                    subStr[6] = '\0';
                    sscanf(subStr, "%s", csName);
                    // read CS offset addr
                    strncpy(subStr, &line[1+6], 6);
                    subStr[6] = '\0';
                    sscanf(subStr, "%x", &csOffset);
                    // read CS length
                    strncpy(subStr, &line[1+6+6], 6);
                    subStr[6] = '\0';
                    sscanf(subStr, "%x", &csLen);
                } else {
                    printf("Unable to determine Header record, skipping file: %s\n", argv[curfile]);
                    break;
                }
                // check estab for duplicate names
                if (findTable(csName) != -1) {
                    printf("Find duplicate external symbol, skipping file: %s\n", argv[curfile]);
                    break;
                } else {
                    csAddr += csOffset;
                    pushTable(csName, csAddr, 1);
                    addCSLenToTable(csName, csLen);
                }
            // end Header record //

            // check other type of records until End record //
            } else if (line[0] != 'E') {
                // process Define record //
                if (line[0] == 'D') {
                    for (int i=0; line[1+12*i] != '\n'; i++) {
                        // read Symbol name
                        strncpy(subStr, &line[1+12*i], 6);
                        subStr[6] = '\0';
                        sscanf(subStr, "%s", symName);
                        // read Symbol addr
                        strncpy(subStr, &line[7+12*i], 6);
                        subStr[6] = '\0';
                        sscanf(subStr, "%x", &symAddr);
                        // check estab for duplicate names
                        if (findTable(symName) != -1) {
                            printf("Find duplicate external symbol, skipping symbol: %s\n", symName);
                            continue;
                        } else {
                            pushTable(symName, csAddr+symAddr, 2);
                        }
                    }
                }
                if (line[0] == 'R') {/*do nothing*/};
            }
            // end != 'E' records

            else if (line[0] == 'E') {
                continue;
            }
        }
        // end reading one file //

        csAddr += csLen;

    }

    // Print all pairs in Table
    printTable();

    fclose(file);
    return 0;
}