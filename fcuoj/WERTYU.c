#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char kb[] = {'`','1','2','3','4','5','6','7','8','9','0','-','=','Q','W','E','R','T','Y','U','I','O','P','[',']','\\','A','S','D','F','G','H','J','K','L',';','\'','Z','X','C','V','B','N','M',',','.','/'};
    char *temp;
    temp = (char*) malloc(105 * sizeof(char));
    while(fgets(temp, 100, stdin) != NULL) {
        for(int i=0; temp[i]!='\0'; i++) {
            if(temp[i] == ' ' || temp[i] == '\n') {
                printf("%c", temp[i]);
                continue;
            }
            for(int j=0; ;j++) {
                if(temp[i] == kb[j]) {
                    printf("%c", kb[j-1]);
                    break;
                }
            }
        }
    }
}