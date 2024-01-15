/*
   Simple attempt to use colour, clear screen etc.
   Will only work on ANSI compliant terminals :
   https://en.wikipedia.org/wiki/ANSI_escape_code
   such as xterm, WSL etc.
*/
//TODO C/P Neill code - understanding:
#include "neillsimplescreen.h"

/* Issue ANSI Codes to clear screen */
void neillclrscrn(void)
{
   printf("\033[2J");
}
//\033 is escape char, 2J is cmnd to clear scrn
/* Issue ANSI Codes to move cursor home */
void neillcursorhome(void)
{
   //int homeCol = 25; //TODO MagicNum
   //int homeRow = 16; //TODO MagicNum
   printf("\033[H");
   // printf("\033[%d;%dH", homeCol, homeRow);
}
// H command to move to home position - what is home?

/* Issue ANSI Codes change foreground (text) colour */
void neillfgcol(const neillcol c)
{
   printf("\033[%dm", c);
}
//x is colour code, c is enum value

/* Issue ANSI Codes to change background colour */
void neillbgcol(const neillcol c)
{
   neillfgcol(c+BACKGROUND);
}
//calls prev func with c+10, (10 ==bkg col code)
//eg if c==31 (RED), func does 31+10=41 (RED_BKG col code)

/* Issue ANSI Codes to reset text/colour styles */
/* Equivalent to running the command 'reset' in the terminal */
void neillreset(void)
{
   printf("\033[0m");
}
//0m resets all text and colour to default

/* May the coding Gods forgive this code
   You really want to give time to other
   processes, rather than sit in a busy loop */
void neillbusywait(const double secs)
{
   clock_t t2;
   const clock_t t1 = clock();
   do{
      t2 = clock();
   }while((t2-t1) < (clock_t)((double)CLOCKS_PER_SEC*secs));
}
/*
Implementation: 
Uses a loop that continuously checks 
the current time against a start time (t1) until the 
specified number of seconds (secs) has passed. 
It uses clock() from <time.h> to get processor time.

Purpose: 
Synchronize certain operations, simulate processing time, 
or create a delay between animations or outputs in a 
console-based application.
*/
//TODO figure out when to use this function
