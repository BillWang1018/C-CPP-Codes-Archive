#include <stdio.h>

#define border 64
#define rowSize border
#define pageSize (border /8)
#define arrSize (rowSize*pageSize)

unsigned char curr[arrSize], next[arrSize];

void clearCurr() {
    int i;
    for(i=0; i<arrSize; i++) curr[i] = 0x00;
}

void clearNext() {
    int i;
    for(i=0; i<arrSize; i++) next[i] = 0x00;
}

void overwriteCurr() {
    int i;
    for(i=0; i<arrSize; i++) curr[i] = next[i];
}

void printHorLine() {
    int i;
    for(i=0; i<rowSize; i++) printf("==");
    printf("\n");
}

void printCurr() {
    int i,j,k;
    /* 
    for i -> max_page (1 page = n rows)
        for j -> char size (data size = n bits)
            for k -> max_col (col size = n cols)

    [j] bit at [i*col_size+k] 
    curr[i*16+k] & (1 << j)
    */
    for(i=0; i<pageSize; i++)
        for(j=0; j<8; j++) {
            for(k=0; k<rowSize; k++) {
                printf("%c ", (curr[i*rowSize+k] & (1 << j)) ? '@' : '.');
            }
            printf("\n");
        }
}

void horMirror() {
    int i,j,k;
    clearNext();
    for(i=0; i<pageSize; i++) for(j=0; j<8; j++) for(k=0; k<rowSize; k++) {
        next[i*rowSize+k] |= ((curr[(pageSize-1-i)*rowSize+k] & (1 << (8-1-j))) || 0) << j;
    }
    overwriteCurr();
}

void verMirror() {
    int i,j,k;
    clearNext();
    for(i=0; i<pageSize; i++) for(j=0; j<8; j++) for(k=0; k<rowSize; k++) {
        next[i*rowSize+k] |= ((curr[i*rowSize+(rowSize-1-k)] & (1 << j)) || 0) << j;
    }
    overwriteCurr();
}

void r90Rotate() {
    int i,j,k;
    clearNext();
    for(i=0; i<pageSize; i++) for(j=0; j<8; j++) for(k=0; k<rowSize; k++) {
        next[i*rowSize+k] |= ((curr[i*8+j+(pageSize-1-k/8)*rowSize] & (1 << (8-1-(k%8)))) || 0) << j;
    }
    overwriteCurr();
}

void l90Rotate() {
    int i,j,k;
    clearNext();
    for(i=0; i<pageSize; i++) for(j=0; j<8; j++) for(k=0; k<rowSize; k++) {
        next[i*rowSize+k] |= ((curr[rowSize-1-i*8-j+k/8*rowSize] & (1 << k%8)) || 0) << j;
    }
    overwriteCurr();
}

int main() {
    clearCurr();
    for (int i=0; i<pageSize/2; i++)
        for (int j=0; j<8; j++)
            curr[(pageSize/2-1-i)*rowSize+i*8+j] = curr[arrSize-8*(pageSize/2-i)-i*rowSize+j] = 0xc0 >> j;
    for (int i=0; i<pageSize; i++) 
        curr[i*rowSize+rowSize/2-1] = curr[i*rowSize+rowSize/2] = 0xff;
    printCurr(); printHorLine();
    horMirror(); printCurr();
    printHorLine();
    verMirror(); printCurr();
    printHorLine();
    r90Rotate(); printCurr();
    printHorLine();
    l90Rotate(); printCurr();


    return 0;
}
/*
......###.......
.....####.......
....##.##.......
...##..##.......
..##...##.......
.##....##.......
##.....##.......
#......##.......
.......###......
.......####.....
.......##.##....
.......##..##...
.......##...##..
.......##....##.
.......##.....##
.......##......#

//printf("(%d, %d) --%d-> (%d, %d)\n", i*8+j+(2-1-k/8)*16, (8-1-(k%8)), ((curr[i*8+j+(2-1-k/8)*16] & (1 << (8-1-(k%8)))) || 0), i*16+k, j);
*/