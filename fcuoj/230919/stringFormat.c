#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 100

typedef struct mystring {
    int size;
    char str[MAX_CHAR];
} mystr;

void swap(mystr *str1, mystr *str2) {
    mystr tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

int checkLunar(int n) {
	return (!(n%4) && (n%100 || !n%400));
}

int checkDate(int y, int m, int d) {
    if(y < 1911) return 0;
    if(m > 12) return 0;
    int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(checkLunar(y) && m == 2) {
        if(d > 29) return 0;
    }
    else {
        if(d > days[m]) return 0;
        return 1;
    }
}

int main() {
    // == SORT STRINGS == //
    size_t size = MAX_CHAR;
    mystr strs[5][MAX_CHAR];
    size_t sizes[5];
    for(int i=0; i<5; i++) {
        char *tmp = strs[i]->str;
        strs[i]->size = getline(&tmp, &size, stdin);
    }

    for(int i=0; i<5; i++) {
        for(int j=0; j<5-1-i; j++) {
            if(strs[j]->size > strs[j+1]->size) {
                swap(strs[j], strs[j+1]);
            }
        }
    }
    for(int i=0; i<5; i++) {
        printf("%s", strs[i]->str);
    }

    // ==CALENDER== //
    int y,m,d;
    scanf("%d/%d/%d", &y, &m, &d);
    
    if(checkDate(y,m,d)) {
        printf("%d/%02d/%d", y-1911, m, d);
    } else {
        printf("Invalid date");
    }

    return 0;
}
