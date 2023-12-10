#include "specific.h"

bsa* bsa_init(void){
    bsa* newBsa = (bsa*)malloc(sizeof(bsa));
    newBsa->head = NULL;
    return newBsa;
}

bool bsa_set(bsa* b, int indx, int d){
    bsaNode* temp = b->head;
    while (temp){
        if (temp->index == indx){
            temp->data = d;
            return true;
        }
        temp = temp->next;
    }
    bsaNode* newNode = (bsaNode*)malloc(sizeof(bsaNode));
    newNode->index = indx;
    newNode->data = d;
    newNode->next = b->head;
    b->head = newNode;
    return true;
}

int* bsa_get(bsa* b, int indx){
    bsaNode* temp = b->head;
    while (temp) {
        if (temp->index == indx){
            return &(temp->data);
        }
        temp = temp->next;
    }
    return NULL;
}

bool bsa_delete(bsa* b, int indx){
    bsaNode* temp = b->head, *prev = NULL;
    while (temp) {
        if (temp->index == indx){
            if (prev){
                prev->next = temp->next;
            } else{
                b->head = temp->next;
            }
            free(temp);
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

int bsa_maxindex(bsa* b){
    int maxIndex = -1;
    bsaNode* temp = b->head;
    while (temp) {
        if (temp->index > maxIndex){
            maxIndex = temp->index;
        }
        temp = temp->next;
    }
    return maxIndex;
}


bool bsa_free(bsa* b){
    bsaNode* temp = b->head, *next;
    while (temp) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    free(b);
    return true;
}

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
    bsaNode* temp = b->head;
    while (temp){
        func(&(temp->data), acc);
        temp = temp->next;
    }
}

void test(void){
    bsa* b = bsa_init();
    assert(b != NULL);
    assert(b->head == NULL);
    bool set_result = bsa_set(b, 1, 10);
    assert(set_result == true);
    int* get_result = bsa_get(b, 1);
    assert(get_result != NULL);
    assert(*get_result == 10);
    bool delete_result = bsa_delete(b, 1);
    assert(delete_result == true);
    get_result = bsa_get(b, 1);
    assert(get_result == NULL);
    bsa_set(b, 2, 20);
    bsa_set(b, 3, 30);
    int max_index = bsa_maxindex(b);
    assert(max_index == 3);
    bool free_result = bsa_free(b);
    assert(free_result == true);
}
