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
void FreeTree(Node* node);
bool checkDuplicate(Node* root1, Node* root2, int maxDepth1, int maxDepth2);

int main(void) {
    char t1; //garbage value
    Node* head1 = MakeNode('A'); //Created pointer node head. Using x/1d shows ascii 65 representing 'A' 
    Node* n1; //Creates node n, with char being set to 0 through calloc

    srand(time(NULL)); //Such that every time rand is called not same number. Either 0 or 1 (L or R)

    for (t1 = 'B'; t1 < 'G'; t1++) { //c is set to first child, condition is until 'F' node is created, increment number of random node being created 
        n1 = MakeNode(t1); //So instead of n being 0, char is passed so that struct node includes characters 'b' -> 'f'
        InsertRandom(head1, n1); //input parent and child
    }

    char t2;
    Node* head2 = MakeNode('A');
    Node* n2;

    for (t2 = 'B'; t2 < 'G'; t2++) { //c is set to first child, condition is until 'F' node is created, increment number of random node being created 
        n2 = MakeNode(t2); //So instead of n being 0, char is passed so that struct node includes characters 'b' -> 'f'
        InsertRandom(head2, n2); //input parent and child
    }

    printf("%s\n", PrintTree(head1));
    printf("%s\n", PrintTree(head2));

    int treeHeight1 = MaxDepth(head1); // Calculate the maximum depth of the tree.
    printf("Maximum depth of the tree: %d\n", treeHeight1);


    int treeHeight2 = MaxDepth(head2); // Calculate the maximum depth of the tree.
    printf("Maximum depth of the tree: %d\n", treeHeight2);

    FreeTree(head1);
    FreeTree(head2);

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

bool checkDuplicate(Node* root1, Node* root2, int maxDepth1, int maxDepth2){
    //Is depth the same?
    if (maxDepth1 != maxDepth2){
        return false;
    }
    //L1 checkingif either one is 0, then not duplicate
    if (root1 || root2 == NULL){
        return false;
    }
    //base case?
    if (root1->c && root2.c == 'F'){
        return;
    }
    //L2 checking
    for (root1.c = 'A'; root1.c < 'G'; root1.c++){
        
    }


    int leftDepth1 = checkDuplicate(root1->left);
    int leftDepth2 = checkDuplicate(root2->left);

    int rightDepth1 = checkDuplicate(root1->right);
    int rightDepth2 = checkDuplicate(root2->right);

    if ()

    if (root1 && root2 == NULL){
        return true;
    }
}


void FreeTree(Node* node) {
    if (node == NULL) {
        return;
    }

    // Recursively free left and right subtrees
    FreeTree(node->left);
    FreeTree(node->right);

    // Free the current node
    free(node);
}

