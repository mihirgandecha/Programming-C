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
int MaxDepth(Node* head);
Node* makeTree(char c);

int main(void) {
    
    srand(time(NULL));

    char c = 'B';

    Node* tree1 = makeTree(c);
    
    Node* tree2 = makeTree(c);

    printf("%s\n", PrintTree(tree1));
    printf("%s\n", PrintTree(tree2));

    int treeHeight1 = MaxDepth(tree1); // Calculate the maximum depth of the first tree.
    int treeHeight2 = MaxDepth(tree2); // Calculate the maximum depth of the second tree.
    
    printf("Maximum depth of the first tree: %d\n", treeHeight1);
    printf("Maximum depth of the second tree: %d\n", treeHeight2);

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

Node* makeTree(char c) {
    if (c > 'G') {
        return NULL; // Return NULL to indicate the end of recursion.
    }
    Node* head = MakeNode('A');
    Node* n = MakeNode(c);
    InsertRandom(head, n);
    head->left = makeTree(c + 1); // Update the left child with the result of the recursive call.
    return head; // Return the current node.
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

int MaxDepth(Node* head){
    if (head == NULL){
        return 0;
    }
    
    int leftDepth = MaxDepth(head->left); // Depth of the left subtree.
    int rightDepth = MaxDepth(head->right); // Depth of the right subtree.

    // Return the maximum depth of left or right subtree, plus 1 for the current node.
    if (leftDepth > rightDepth){
        return leftDepth + 1;
    }
    else{
        return rightDepth + 1;
    }
}


