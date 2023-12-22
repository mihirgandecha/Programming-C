#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXCMND 100
#define MAXTOKENSIZE 20
#define strsame(A,B) (strcmp(A, B)==0) //TODO: Does this need to be capitalised?
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define NOEXIT_ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d \n", PHRASE, __FILE__, __LINE__); }

struct prog{
   char wds[MAXCMND][MAXTOKENSIZE];
   int cw; 
   bool endReached;
};
typedef struct prog Program;

//Main broken down:
void validArgs(int argc);
FILE* openFile(char* filename);
Program* initTurtle(void);
void readWords(FILE* fttl, Program* turtle);
void runProgram(Program* turtle);

//Grammar:
bool Prog(Program *turtle);
bool Inslst(Program *turtle);
bool Ins(Program *turtle);
bool Fwd(Program *turtle);
bool Num(Program *turtle);
bool Rgt(Program *turtle);
bool Ltr(char var);
bool Var(Program *turtle);
bool Varnum(Program *turtle);
bool Col(Program *turtle);
bool Word(Program* turtle);
bool Item(Program* turtle);
bool Items(Program* turtle);
bool Lst(Program* turtle);
bool Loop(Program *turtle);
bool Op(Program* turtle);

//Testing:
void freeTurtle(Program* turtle);

void test(void);

