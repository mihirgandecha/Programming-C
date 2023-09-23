// Sums are computed.
#include <stdio.h>

int main(void) {

    int cnt = 0;
    float sum = 0.0, x;
    printf("Input some numbers: ");

    while (scanf("%f", &x) == 1) {
        cnt = cnt + 1;
        sum = sum + x;
    }

    printf("\\n%s%5i\\n%s%5f\\n\\n", "Count:", cnt, "Sum: ", sum);
    return 0;
}

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