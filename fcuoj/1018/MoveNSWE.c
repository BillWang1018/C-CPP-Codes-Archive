#include <stdio.h>
int main() {
    int x=0, y=0;
    char c;
    while(1) {
        scanf("%c", &c);
        if(c == 'Z') break;
        if(c == ' ') continue;
        switch(c) {
            case 'N':
                y++;
                break;
            case 'S':
                y--;
                break;
            case 'W':
                x--;
                break;
            case 'E':
                x++;
                break;
        }
    }
    printf("X:%d Y:%d", x, y);
}