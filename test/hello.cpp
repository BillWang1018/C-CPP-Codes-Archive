#include <iostream>
using namespace std;
int main() {
    int b=2;
    int *a = &b;
    printf("%p", a);
    return 0;
}