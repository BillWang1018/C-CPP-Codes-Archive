#include <stdio.h>
#include "sicKeywords.h"

int main() {
    char str[10] = "WTF\0";
    int info = getopInfo(str);
    printf("word: %s | return: %#06X | op: %02x | fmt: %d\n", str, info, info>>4, info%16);
    return 0;
}