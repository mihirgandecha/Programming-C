// Sums are computed.
//We can use the line 12 to create a coin simulator
#include <stdio.h>

int main(void) {

//First the code initialises two types of variables
    int cnt = 0;
    float sum = 0.0, x; //2 float varoables declared. x is full of garbage.
    printf("Input some numbers: ");

    while (scanf("%f", &x) == 1) { //WHILE USERS ARE ENTERING A FLOAT, increase the CNT AND ADD USER INPUT INTO SUM %f is a floating type. while means something happens inside brackets and if TRUE, next instruction executed. 
    /*if failed, returns 0, 1 is SUCCESS. 
    This means any number of values can be stored in x. But the value of the whole function call is the total number of numbers successfully scanned.
    If TRUE, then do all these instructions.
    Equality is tested with == sign. If you want to check that something is the same as something else. */     
        cnt = cnt + 1; //add one to counter
        sum = sum + x; //add value x to sum
    }

    printf("\n%s%5i\n%s%5f\n\n", "Count:", cnt, "Sum: ", sum);
    //Print new line, then print string (%s) - which looks at line and is "Count", THEN Print integer in box space of 5 
    return 0;
} /* Puts everything into space called BOOKER. When you press enter, it takes BOOKER. Flow of characters.

*/

/*
Sure, let's use the analogy of a **"Coin-Counting Machine"** to explain a `while` loop:

Imagine you have a coin-counting machine. You pour coins into a funnel at the top, and the machine counts and sorts each coin until the funnel is empty. 

1. **Initialization**: Before you start, the machine's screen displays "Total Coins: 0" and "Total Value: $0.00". This is analogous to initializing your loop control variables before the loop starts.

2. **The Funnel as the Condition**: As long as there's a coin ready to drop from the funnel (i.e., the funnel is not empty), the machine continues its counting operation. This is the `while` loop's condition. The loop keeps iterating as long as the condition is true.

3. **The Counting Operation**: Each time a coin drops, the machine:
   - Identifies the coin (e.g., dime, quarter).
   - Adds 1 to the "Total Coins" count.
   - Adds the coin's value to the "Total Value".
   
   This operation is analogous to the body of the `while` loop, where the action or computation happens during each iteration.

4. **End of Loop**: Once the funnel runs out of coins (i.e., is empty), the machine stops counting. This is like the loop's condition becoming false, causing the loop to exit.

5. **Final Result**: The machine's screen now displays the final count and total value of the coins. After the loop in a program, you might display or use the results computed within the loop.

In the context of the code you shared:
- The "coin" is each number the user inputs.
- The "funnel being empty" is like the user inputting something that isn't a number or causing `scanf` to return a value other than 1.
- The "counting operation" involves updating the `cnt` variable (like "Total Coins") and summing the value with the `sum` variable (like "Total Value").

I hope this analogy helps in visualizing the functioning of a `while` loop!

Lets do a pound coin machine counter? or uk machine counter?
*/