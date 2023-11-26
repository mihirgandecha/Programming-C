#include "general.c"

typedef struct data {
    int i;
    struct data* next;
} Data;

Data* allocateData(int i);
void printList(Data* l);

int main(void){
    int i;
    Data* start, *current;
    start = current = NULL;

    printf("Enter the first number: ");
    if (scanf("%i", &i) == 1) {
        start = current = allocateData(i);
    } else {
        on_error("Couldn’t read an int");
    }

    printf("Enter more numbers, end with char to stop: ");
    while (scanf("%i", &i) == 1) {
        current->next = allocateData(i);
        current = current->next;
    }

    printList(start);
    // Should Free List

    return 0;
}

Data* allocateData(int i){
    Data* p;
    p = (Data*)ncalloc(1, sizeof(Data));
    p->i = i;
    p->next = NULL;
    return p;
}

void printList(Data* l){
    printf("\n");
    do {
        printf("Number: %i\n", l->i);
        l = l->next;
    } while (l != NULL);
    printf("END\n");
}
