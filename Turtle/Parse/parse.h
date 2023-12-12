#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#define strsame(A,B) (strcmp(A, B)==0) //does this mean we are defaulting it to be false?
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}


struct prog{
   char wds[MAXNUMTOKENS][MAXTOKENSIZE]; //What is stored in each?
   int cw; // Current Word
};
typedef struct prog Program;

bool TurtleInit(Program *turtle);
bool Start(Program *turtle);
bool Inslst(Program *p);
bool Ins(Program *p);
// bool Fwd(Program *p);
// bool Rgt(Program *p);
// int Num(Program *p);

void test(void);

