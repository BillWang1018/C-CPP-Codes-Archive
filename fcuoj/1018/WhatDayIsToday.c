#include <stdio.h>
int main() {
    int num;
    scanf("%d", &num);
    switch (num) {
        case 1:
            printf("今天是星期一");
            break;
        case 2:
            printf("今天是星期二");
            break;
        case 3:
            printf("今天是星期三");
            break;
        case 4:
            printf("今天是星期四");
            break;
        case 5:
            printf("今天是星期五");
            break;
        case 6:
            printf("今天是星期六");
            break;
        case 7:
            printf("今天是星期七");
            break;
      default:
        	printf("輸入錯誤");
        	break;
    }

}