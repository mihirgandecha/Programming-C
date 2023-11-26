#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node{
    int data; //Cargo or data
    struct Node* next;
} Node;

int main(void){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->data = 10; //Load data into first car
    head->next = NULL;

    assert(Node head->data == 10);

    return 0;
}
