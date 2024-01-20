#include "stack.h"
#include "specific.h"
#include "../../Turtle/Interp/interp.h"


int main(void)
{
    Program *turtle = initTurtle();
    // Initialize the stack
    stack* s = stack_init();

    free(turtle);

    // // Create a loop context for the Turtle code
    // loop_context context;
    // context.variable = 'A';
    // context.values = {1, 2, 3, 4, 5, 6, 7, 8};
    // context.instruction = "FORWARD 5 RIGHT 45";

    // // Push the loop context onto the stack
    // stack_push(s, context);

    // // While there are contexts on the stack, execute them
    // while (s->size > 0) {
    //     // Pop the top context from the stack
    //     loop_context current_context;
    //     stack_pop(s, &current_context);

    //     // For each value in the context's list, execute the instructions
    //     for (int i = 0; i < sizeof(current_context.values) / sizeof(current_context.values[0]); i++) {
    //         current_context.variable = current_context.values[i];

    //         // Execute the instructions (assuming execute_instructions is implemented elsewhere)
    //         execute_instructions(current_context.instruction);
    //     }
    // }

    // Free the stack
    stack_free(s);

    return 0;
}