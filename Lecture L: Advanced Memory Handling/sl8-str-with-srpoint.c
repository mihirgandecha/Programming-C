//Structures with Self-Referential Pointers
//Structure that points to something else with same type!

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct data {
    int num;
    //C Compiler recognises - has to be pointer!
    struct data* next;
};

typedef struct data data;

int main(void) {
    //all have num, next
    data c = {5, NULL};
    data b = {17, &c};
    data a = {11, &b};

    printf("%i\n", a.num);
    data* p = &a; //points at address of a
    printf("%i\n", p->num);

    //REMEMBER! Take HOME!
    p = p->next; //points to c next
    printf("%i\n", p->num);
    p = p->next;
    printf("%i\n", p->num);

    return 0;
}