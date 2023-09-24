//This Project aims to simulate a coin collecter, where the scanf makes the user input the different varieties of coins defined, then sums it.

#include <stdio.h>
#define POUNDSYMBOL '£'
#define TWOPOUND 2.00f
#define POUND 1.00f //f is suffix for float. can use L for long double but check how long it takes
#define FIFTYP 0.50f //cant use '50p' as rule is that is cant start with number
#define TWNTYP 0.20f
#define TENP 0.10f
#define FIVEP 0.05f
#define TWOP 0.02f
#define ONEP 0.01f

int main(void){

    int cnt = 0;
    float a, payout;
    printf("Welcome to Metro Bank. Please insert your coins and out machine will compute the sum.")
    printf("What coins do you have? You can type the following for the respected value:\nTWOPOUND for £2.00 \nPOUND for £1.00 \n FIFTYP for £0.50 \nTWNTYP for £0.20 \nTENP for £0.10 \n FIVEP for £0.05 \n TWOP for £0.02 \n ONEP for £0.01 \n");
    while(scanf("%f", &a) == 1){

        payout = payout + a;
        cnt = cnt + 1;
    }

    printf("\n%s%5i", "Number of Coins Deposited: ", cnt);
    printf("Does this sound correct to you? Please say (y) for yes, or (n) for no");
    if(scanf("%s") == 'y'){
        //continue to sum
    }
    else{
        printf("The machine will now return your money. Feel free to try again.");
        //go back to main
    }

    printf("\n%s%5f", "Your Payout: ", payout);
    printf("Does this sound correct to you? Please say (y) for yes, or (n) for no");
    if(scanf("%s") == 'y'){
        //continue to final call
    }
    else{
        printf("The machine will now return your money. Feel free to try again.");
        //go back to main
    }

    //FINAL CALL SUMMARY

    printf("\n%s%5i\n%s%5f\n%s\n", "Printing receipt for %i coins equating to POUNDSYMBOL%f. Please head to the front counter to collect your payout. Thank you for using Metro Bank. Have a lovely day!")
    return 0;
}