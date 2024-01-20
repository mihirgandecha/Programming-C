#pragma once

#define FORMATSTR "%i"
#define ELEMSIZE 20
#define STACKTYPE "Linked"

typedef struct{
   char var[ELEMSIZE];
   bool inUse;
} Instruction;

struct dataframe {
   stacktype i;
   struct dataframe* next;
};
typedef struct dataframe dataframe;

struct stack {
   dataframe* start;
   int loopIndex;
   int size;
   Instruction* inst;
};



/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, stacktype i);
/* Take element from top */
bool stack_pop(stack* s, stacktype* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Optional? */

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s,  stacktype* d);
/* Make a string version - keep .dot in mind */
void stack_tostring(stack*, char* str);

