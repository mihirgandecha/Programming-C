#pragma once
#include "general/general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#define MAXCMND 100
#define MAXTOKENSIZE 20
#define MIN_ARGS 3
#define EXPECTED_VARLEN 2
#define STRSAME(A,B) (strcmp(A, B)==0) 
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define DEBUG(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d \n", PHRASE, __FILE__, __LINE__); }
#define COL 51
#define ROW 33
#define SCOL 25
#define SROW 17
#define SCR_DELAY 0.05
#define M_PI 3.14159265358979323846264338327950288
#define HALFCIRC 180.00
#define FULLCIRC 360.00
#define DOUBLE 2
#define BUFFER 10000
#define MAX_VARS 26
#define THRESHHOLD 1e-9
#define INDEX(c) ((int)(c - 'A'))
   //ps2pdf PSFILENAME output.pdf

typedef struct stack stack;
typedef char* stacktype;

typedef struct{
   char var[MAXTOKENSIZE];
   bool inUse;
} Variable;

struct prog{
   char wds[MAXCMND][MAXTOKENSIZE];
   int cw; 
   int col, row;
   double rAngle;
   bool isScreen;
   char SCREEN[ROW][COL];
   char colour;
   char* setColour;
   Variable store[MAX_VARS];
   bool setUsed[MAX_VARS];
   char* varTemp;
   int varIndx;
   stack* s; 
};
typedef struct prog Program;

bool storeList(Program *turtle, int startList, int cList);

//Start Parser:
void validArgs(int argc);
FILE* openFile(char* filename);
Program* initTurtle(void);
void readWords(FILE* fttl, Program* turtle);
void runProgram(Program* turtle);
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
bool Word(Program* turtle);
bool Lst(Program* turtle);
bool Items(Program* turtle);
bool Item(Program* turtle);
bool Pfix(Program* turtle);
bool Op(Program* turtle);
void splitIntoWords(char* str, char* words);
bool checkNull(Program *turtle);
//End Parser

//Interpreter Functions:
void writeFile(char* filename, Program *turtle);
//Screen:
void initScrn(Program *turtle);
void printtoscreen(Program *turtle);
//Fwd Int:
void varFwd(Program *turtle);
bool intFwd(Program *turtle, double distance);
bool Bresenham(Program *turtle, int rowEnd, int colEnd, int dRow, int dCol);
bool isWithinBounds(int row, int col);
void test_isWithinBounds(void);
bool drawPoint(Program *turtle, int row, int col);
void updatePoints(Program *turtle, int error, int dRow, int dCol, int signRow, int signCol);
//TODO readjust:
void testBresenham(void);
//Lst Int:
bool storeList(Program *turtle, int startList, int cList);
//Col Int:
void setCol(Program *turtle, char* colour);
char* subStr(char *str);
void test_subStr(void);
//Rgt Int:
void varAngle(Program *turtle);
//Num Int:
int compareFloat(double a, double b);
void test_compareFloat();
double degToRad(double degrees);
void degToRadTest(void);
//Pfix Int:
void intPfxix(Program *turtle);
//Stack:
stack* stack_init(void);
void stack_push(stack* s, stacktype d);
bool stack_pop(stack* s, stacktype* d);
bool stack_free(stack* s);
bool stack_peek(stack*s,  stacktype* d);
void stack_tostring(stack*, char* str);
//Test:
void test(void);
// void queue_push(stack* s, stacktype d);
// bool queue_pop(stack* s, stacktype* d);
// bool queue_free(stack* s);
