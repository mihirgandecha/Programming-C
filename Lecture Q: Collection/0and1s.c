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

void Start(Program *p);
void Code(Program *p);
void Statement(Program *p);

int main(void)
{
   Program* prog = calloc(1, sizeof(Program)); //making space for entire structure of size 1
   int counter = 0;
   while(scanf("%s", prog->wds[counter++])==1&& counter<MAXNUMTOKENS);
   Start(prog); //Run begin 
   printf("Parsed OK\n"); //Output once finished 
   //while the program takes user input, increase counter within first dimension 
   return 0;
}


//Testing that the first input is BEGIN
void Start(Program *p)
{
   if(!strsame(p->wds[p->cw], "BEGIN")){ //WORKS! strsame returns true or false (default false)
      ERROR("No BEGIN statement ?"); 
   }
   p->cw += 1; //otherwise increases counter by 1
   Code(p);
}

void Code(Program *p)  //Recursive function to take END + STATEMENT
{
   if(strsame(p->wds[p->cw], "END")){ // counter at 1 after 
      return;
   }
   else{
      Statement(p); //call Statement 
      p->cw = p->cw + 1; //should this be here or in statement?
   }
   Code(p);
}

void Statement(Program *p)
{
   if(strsame(p->wds[p->cw], "ONE")){
      printf("1\n");
      // p->cw += 1;
      return;
   }
   if(strsame(p->wds[p->cw], "NOUGHT")){
      // p->cw += 1;
      printf("0\n");
      return;
   }
   ERROR("Expecting a ONE or NOUGHT ?");
}
