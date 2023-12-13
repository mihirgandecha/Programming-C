#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXCMND 100
#define MAXTOKENSIZE 20
#define MAXCOL 33
#define MAXROW 51
#define strsame(A,B) (strcmp(A, B)==0) //does this mean we are defaulting it to be false?
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}


struct prog{
   char cmnd[MAXCMND][MAXTOKENSIZE]; //What is stored in each?
   int cw; // Current Word
   int size;
};
typedef struct prog Program;

// struct board{
//    int b[MAXCOL][MAXROW];
// };
// typedef struct board Board;

// bool TurtleInit(Program *turtle);
bool Start(Program *turtle);
bool Inslst(Program *turtle);
bool Ins(Program *turtle);
bool Fwd(Program *turtle);
bool Rgt(Program *turtle);
bool Num(Program *turtle, double *Num);

void test(void);

