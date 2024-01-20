#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
//Float library used to test that any float can be used
#include <float.h>


#define MAXCMND 100
#define MAXTOKENSIZE 20
#define MIN_ARGS 2
#define EXPECTED_VARLEN 2
#define STRSAME(A,B) (strcmp(A, B)==0) 
#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHRASE, __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define DEBUG(PHRASE) {fprintf(stderr, "Fatal Error %s occurred in %s, line %d \n", PHRASE, __FILE__, __LINE__); }
#define COL 51
#define ROW 33
#define SCOL 25
#define SROW 16
#define SCR_DELAY 0.05

#define M_PI 3.14159265358979323846264338327950288
#define HALFCIRC 180.00
#define FULLCIRC 360.00
#define DOUBLE 2
#define BUFFER 10000

#define MAX_VARS 26
#define THRESHHOLD 1e-9

//feed in turtle.varTemp to get index
#define INDEX(c) ((int)(c - 'A'))

//Structure for implementing LOOP:
// typedef struct{
//    double instruct[100];
//    int top;
// } Stack;

// Data Structure for storing <NUM>
typedef struct{
   char var;
   double value;
} storeNum;

// typedef int stacktype;
// typedef struct stack stack;
// struct dataframe {
//    stacktype i;
//    struct dataframe* next;
// };
// typedef struct dataframe dataframe;

// struct stack {
//    /* Underlying array */
//    dataframe* start;
//    int size;
// };
// //Data Structure for storing <NUM>
typedef struct{
   char var[MAXTOKENSIZE];
   bool inUse;
} Variable;


struct prog{
   char wds[MAXCMND][MAXTOKENSIZE];
   int cw; 
   bool endReached;
   int col, row;
   double distance;
   //Storing rotation of curser in degrees, and rAngle for radians
   double rot;
   //TODO Change to radRot:
   double rAngle;
   bool numUsed;
   bool varUsed;
   bool setUsed[MAX_VARS];
   int index;
   char SCREEN[ROW][COL];
   char colour;
   char* strcol;
   char* varTemp;
   int loopItems[MAX_VARS];
   int loopIndx;
   storeNum* simpleSet[MAX_VARS];
   Variable* store[MAX_VARS];
};
typedef struct prog Program;


static size_t test(void);

//Screen:
void initScrn(Program *turtle);
void printtoscreen(Program *turtle);
bool intFwd(Program *turtle);
void setCol(Program *turtle, char* colour);
bool Bresenham(Program *turtle, int rowStart, int colStart, int rowEnd, int colEnd, int dRow, int dCol);
void testBresenham(void);
char* subStr(char *str);
void test_subStr(void);
bool isWithinBounds(int row, int col);
bool isWithinBounds(int row, int col);
void test_isWithinBounds(void);

bool drawPoint(Program *turtle, int row, int col);
void writeFile(char* filename, Program *turtle);
void varAngle(Program *turtle);
void varFwd(Program *turtle);



//Interpret SET:
//Simple function for interpreting SET Ltr -> <NUM>
// bool setNum(char varName, double value);
// void initVar(Program* turtle, int index, double value);
void interpSetNum(Program* turtle);
void test_interpSetNum_edge_cases(void);

bool freeStoreNum(Program* turtle);
int compareFloat(double a, double b);
void test_compareFloat();

bool store(Program* turtle);
bool freeStorage(Program* turtle);





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
void initPos(Program *turtle);
double degToRad(double degrees);
void degToRadTest(void);

/*
Pseudo code:
Variable* store[MAX_VARS];
typedef struct{
   char var[MAXTOKENSIZE];
   bool inUse;
} Variable;



1. get index by defining Macro to calculate eg 'B' - 'A'
2. we can now store A->Z (the index), into array
3. Within the array, storing the string which can be later converted:
         ie if COLOUR $B, get index of B and check bool flag if stored
               if yes then correct and get value
               if no then return error
         ie2. If SET $B (2), 2 needs to be converted into string first then stored

*/
