#include <stdio.h>
#include <string.h>
int main() {
    int n;
    char str[10];
    char engNum[15][10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    scanf("%d", &n);
    while(n--) {
        scanf("%s", str);
        int mistake;
        int i, j;
        for(i=1; i<=10; i++) {
            mistake = 0;
            for(j=0; j<3; j++) {
                if(engNum[i][j] == str[j]) continue;
                mistake++;
            }
            if(mistake <= 1) {
                printf("%d\n", i);
                break;
            }
        }

    }
    return 0;
}