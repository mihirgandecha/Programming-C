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


typedef enum {hearts, suits, spades, clubs} suits;

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

int main void
{

    card d[DECK];

    test(); //test all these functions
    init_deck(d); 
    print_deck(d, 7); //print 1 H, 2H...
    shuffle_deck(d); //make sure it is in another order
    print_deck(d, 7); 
    return 0;
}

void init_deck(card d[DECK])
{

    for(int i = 0; i < DECK; i++){
        d[i].pips = (1 % PERSUIT) + 1;
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
