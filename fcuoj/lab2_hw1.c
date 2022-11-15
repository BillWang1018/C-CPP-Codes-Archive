#include <stdio.h>
int main() {
    int value;
    while(scanf("%d", &value)) {
        if(value >= 60)
            if(value >= 70)
                if(value >= 80)
                    if(value >= 90)
                        printf("A");
                    else
                        printf("B");
                else
                    printf("C");
            else
                printf("D");
        else
            printf("F");
        printf("\n");
    }
}