#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define STRSIZE 5000

struct node {
    char c; //i.e. 'A' in line 23 for root node (1-byte)
    struct node* left; //pointer to another node structure (4 or 8 depending on if 32 or 64 bit)
    struct node* right;
};

typedef struct node Node;

Node* MakeNode(char c);
void InsertRandom(Node* t, Node* n);
char* PrintTree(Node* t);

int main(void) {
    char c; //garbage value
    Node* head = MakeNode('A'); //Created pointer node head. Using x/1d shows ascii 65 representing 'A' 
    Node* n; //Creates node n, with char being set to 0 through calloc

    srand(time(NULL)); //Such that every time rand is called not same number. Either 0 or 1 (L or R)

    for (c = 'B'; c < 'G'; c++) { //c is set to first child, condition is until 'F' node is created, increment number of random node being created 
        n = MakeNode(c); //So instead of n being 0, char is passed so that struct node includes characters 'b' -> 'f'
        InsertRandom(head, n); //input parent and child
    }

    printf("%s\n", PrintTree(head));

    return 0;
}

//If NULL, means no node on the left/right
Node* MakeNode(char c) {
    Node* n = (Node*)calloc(1, sizeof(Node)); //Creates memory for struct Node (so that point left right is used too) space for every node created, setting all bits of mem block to 0 
    assert(n != NULL); //Check that calloc worked and memory has been allocated, use p *n
    n->c = c; //storing whatever is in n to the structure (storing the character). So we allocated memory, and now storing 'A' in the structure.
    return n;
}
//understand what is causing left/right to be set to NULL
void InsertRandom(Node* t, Node* n) { //input is parent (where the node is inserted) and child (the node to be inserted), such that loop includes child 'B' -> 'F' (only char is changing in struct so far)
    if ((rand() % 2) == 0) { /* Left */
        if (t->left == NULL) {
            t->left = n; //want to keep calling this function until t-left/right == NULL
        } else {
            InsertRandom(t->left, n);
        }
    } else { /* Right */
        if (t->right == NULL) {
            t->right = n;
        } else {
            InsertRandom(t->right, n);
        }
    }
}

char* PrintTree(Node* t) {
    char* str;
    assert((str = calloc(STRSIZE, sizeof(char))) != NULL);

    if (t == NULL) {
        strcpy(str, "*");
        return str;
    }

    sprintf(str, "%c(%s)(%s)", t->c, PrintTree(t->left), PrintTree(t->right));
    return str;
}
