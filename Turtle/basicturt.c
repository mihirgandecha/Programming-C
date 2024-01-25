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


// bool Bresenham(Program *turtle, int rowEnd, int colEnd, int dRow, int dCol){
//     int signRow = turtle->row < rowEnd ? 1 : -1;
//     int signCol = turtle->col < colEnd ? 1 : -1;
//     dRow = abs(dRow);
//     dCol = abs(dCol);
//     if(!drawPoint(turtle, turtle->row, turtle->col)){
//         return false;
//     }
//     int error = dCol - dRow;
//     while((dRow > 1 || dCol > 1) && ((turtle->row != rowEnd) || (turtle->col != colEnd))){          
//         int doubleError = DOUBLE * error;
//         if(doubleError >= -dRow){
//             error -= dRow;
//             turtle->col += signCol;
//         }
//         if(doubleError <= dCol){
//             error += dCol;
//             turtle->row += signRow;
//         }
//         if(!drawPoint(turtle, turtle->row, turtle->col)){
//             return false;
//         }
//     }
//     printtoscreen(turtle);
//     return true;
// }