#pragma once

// #define FORMATSTR "%i"
#define ELEMSIZE 20
#define STACKTYPE "Linked"

struct inst {
   struct instruction* next;
};
typedef struct inst inst;

struct dataframe {
   stacktype i;
   struct dataframe* next;
};
typedef struct dataframe dataframe;

struct stack {
   dataframe* start;
   dataframe* end;
   int size;
};




/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void pushItem(Program* turtle, stacktype item);
/* Take element from top */
bool stack_pop(stack* s, stacktype* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Optional? */

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s,  stacktype* d);
/* Make a string version - keep .dot in mind */
void stack_tostring(stack*, char* str);

