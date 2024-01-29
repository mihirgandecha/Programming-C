#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXCMND 100
#define MAXTOKENSIZE 20
#define EXPECTED_ARGS 2
#define EXPECTED_VARLEN 2
#define STRSAME(A,B) (strcmp(A, B)==0) 
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define DEBUG(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d \n", PHRASE, __FILE__, __LINE__); }

struct prog{
   char wds[MAXCMND][MAXTOKENSIZE];
   int cw; 
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
bool Rgt(Program *turtle);
bool Col(Program *turtle);
bool Loop(Program *turtle);
bool Set(Program *turtle);

bool Varnum(Program *turtle);
bool Var(Program *turtle);
bool Ltr(Program *turtle);
bool Num(Program *turtle);

//pointer placement?
bool Word(Program* turtle);

bool Lst(Program* turtle);
bool Items(Program* turtle);
bool Item(Program* turtle);

bool Pfix(Program* turtle);
bool Op(Program* turtle);

void splitIntoWords(char* str, char* words);
bool checkNull(Program *turtle);
void test(void);

