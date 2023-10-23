#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int a;
    int b;
} Term;

Term *mats[30] = {0};

void print_storage_info(const char* str, const Term* next)
{
    if (next)
        printf("%s location: %p.\n",
               str, (void*)next);
    else
        printf("Allocation failed.\n");
}

int main() {
    printf("Size of Term  = %X | ", sizeof(Term));
    printf("Size of Term* = %X\n", sizeof(Term*));
    for(int i=0; i<30; i++)
        mats[i] = (Term*) realloc(mats[i], sizeof(Term));
    char c = 'a';
    // scanf("%c", &c);
    c -= 'a';
    
    print_storage_info("Old mats[c]", mats[c]);

    mats[c][0].a = 'A';
    mats[c][0].b = 'a';

    printf("%c | %c\n", mats[c][0].a, mats[c][0].b);

    Term* tmp = (Term*) realloc(mats[c], sizeof(Term) * 10);
    
    print_storage_info("New mats[c]", mats[c]);

    printf("=======================================\n");

    mats[c] = tmp;

    for(int i=1; i<10; i++) {
        
        // Term *t = (Term*) malloc(sizeof(Term));
        // t->a = 'A'+i;
        // t->b = 'a'+i;
        // mats[c][i] = *t;
        mats[c][i].a = 'A'+i;
        mats[c][i].b = 'a'+i;
    }

    Term *t = mats[c];
    for(int i=0; i<10; i++, t++) {
        print_storage_info("ptr_t", t);
        print_storage_info("mats[c][i]", &mats[c][i]);
        printf("Idx: %c | %c\n", mats[c][i].a, mats[c][i].b);
        printf("Ptr: %c | %c\n", (t)->a, (t)->b);
    }

    return 0;
}