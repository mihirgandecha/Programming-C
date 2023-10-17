/*Playing Cards Example:
    -There are 13 cards in each suit A-K
    -4 suits
    -52 cards in a deck
    */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//Step 1: Define the constants and data
#define SUIT 4
#define PERSUIT 13
#define DECK (SUIT * PERSUIT)
#define SHUFFLE 3


//defining a new data type called suits, where 4 suits are defined as constants
/*Why? The 4 constants that are #define can have an integer type
However how can you define the suits themselves?
WE USE THIS TO DEFINE A SET NUMBER OF NAMED CONSTANTS THAT REPRESENTS A SPECIFIC DOMAIN!
Here we are calling the data type suits

Note we can typedef straight away!*/


typedef enum {hearts, diamonds, spades, clubs} suit;

/* 3 Functions:
    1. Initialise the deck of cards. SET IT UP! To do this we have to create a structure.
    Structure includes the suit, and the card itself (A-King)

    2. Print the deck function. Note there is no way to check and test!
    Use STRINGS!

    3. Shuffle Deck - take one card and swaps.

    ALL OF THIS SHOULD BE IN .h FILE! YOU NEED TO SEE MAIN!
*/

struct card {
    suit st;
    int pips;
};

//if we don't then we need to call struct card, instead of just card
typedef struct card card;

void shuffle_deck(card d[DECK]);
void init_deck(card d[DECK]);
void print_deck(card d[DECK], int n);
void test(void);

int main (void)
{

    card d[DECK];

    test(); //test all these functions
    init_deck(d); 
    print_deck(d, 7); //print 1 H, 2H...
    shuffle_deck(d); //make sure it is in another order
    print_deck(d, 7); 
    return 0;
}

void init_deck(card d[DECK]) //flowchart
{

    for(int i = 0; i < DECK; i++){
        //first we are assigning numbers
        d[i].pips = (i % PERSUIT) + 1; //first we are accessing i-th element of array of type card
        //we are assigning (1 % PERSUIT) + 1

        //here we are assigning suit
        switch (i / PERSUIT){
            case hearts: d[i].st = hearts;
            break;

            case diamonds: d[i].st = diamonds;
            break;

            case spades: d[i].st = spades;
            break;

            case clubs: d[i].st = clubs;
            break;

            default:
                assert (false);
        }
    }
}

//REMEMBER ARRAY IS NOT COPIED!
//Cards out on table. Take 2 and swap them
//keep shuffling fixed number of times

void shuffle_deck(card d[DECK])
{
    for(int i = 0; i < SHUFFLE*DECK; i++){ 
        int n1 = rand()%DECK; 
        int n2 = rand()%DECK; //choose 2 numbers randomly (cell of array). % ensures it is within range of valid card positions
        //make sure you create a copy!!!
        card c = d[n1]; d[n1] = d[n2]; d[n2] = c;
        //c is a temporary new card, and is used to store card at position n1 
        // d[n1] = d[n2] means that the card at position n1 is replaced with card at position n2 
        //now c is the replaced card
    }
}

//print deck - give me array of cards - i want to print out the first n cards
void print_deck(card d[DECK], int n) {
    for (int i = 0; i < n; i++) {
        switch (d[i].pips) {
            case 11:
                printf("Jack"); //if pip is 11 then print Jack
                break; //replace with string
            case 12:
                printf("Queen");
                break;
            case 13:
                printf("King");
                break;
            default: // for any values of pips, print this:
                printf("%2i", d[i].pips);
        }

        switch (d[i].st) {
            case hearts:
                printf(" of Hearts\n");
                break;
            case diamonds:
                printf(" of Diamonds\n");
                break;
            case spades:
                printf(" of Spades\n");
                break;
            default:
                printf(" of Clubs\n");
        }
    }
    printf("\n");
}

void test(void) {

    int n = 0;
    card d[DECK];
    init_deck(d); //Direct assignment

//Check initialising deck
    card c = {hearts, 10}; //Look at the 10th cell of array, and see if it is 10 Hearts
    assert(d[9].pips == c.pips); //could just be d[10] == "hearts"
    assert(d[9].st==c.st);

//How can we test shuffle deck?
//shuffle deck 1000 times 1 time in 52 aprox we should pull a 10 Hearts
    for(int i = 0; i < 1000; i++){
        shuffle_deck(d); //Happens 1 time in52 ?

        if((d[0].st == c.st) && (d[0].pips == c.pips)){
            n++;
        }
    } // Is this a reasonable test ?
    assert((n > 10) && (n < 30)); //between 10 and 30
}







