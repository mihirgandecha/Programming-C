#include "parse.h"
#include <math.h>


#define MAXCMND 100
#define MAXTOKENSIZE 20
#define MAXCOL 33
#define MAXROW 51
#define PI 3.14159265358979323846
#define STRAIGHT_ANGLE 180.00
#define OUTBOUND -1
// int main(void){
//     Program* turtle = (Program*)calloc(1, sizeof(Program));
//     if (!turtle){
//         ERROR("Turtle failed to initialise!\n");
//         return 1;
//     }
//     Init(turtle);
//     printf("Enter Turtle Commands:\n");
//     // if (scanf("%s %s", turtle->cmnd[turtle->cw]) != 1 || !strsame(turtle->cmnd[turtle->cw], "START")){
//     //     ERROR("No 'START' statement!\n");
//     //     return false;
//     // }
//     Prog(turtle);
//     printf("Parsed OK\n");
//     free(turtle);
//     return 0;
// }

// int main(int argc, char* argv[]){
//     test();
//     if(argc != 2){
//         ERROR("Error on argv[0]\n");
//         exit(EXIT_FAILURE);
//     }
//     FILE* fttl = fopen(argv[1], "r");
//     if(!fttl){
//         ERROR("Cannot read from argv[1] \n");
//         fclose(fttl);
//         exit(EXIT_FAILURE);
//     }
//     Program* turtle = (Program*)calloc(1, sizeof(Program));
//     if (!turtle){
//         ERROR("Turtle failed to initialise!\n");
//         fclose(fttl);
//         exit(EXIT_FAILURE);
//     }
//     int i = 0;
//     while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
//         i++;
//     }
//     if(!Prog(turtle)){
//         ERROR("Prog did not work");
//     }
//     puts("\nPassed Ok.");
//     fclose(fttl);
//     free(turtle);
//     return 0;
// }

//Need to first know how to take ttl and run
// void Input(FILE ttl, Program *turtle){
//     //Need to strip the null character
// FILE *fp = 
//     while(fscanf("%s", turtle->cmnd[turtle->cw++]) != 1){
//     }
// }

// void Init(Program *turtle){
//     turtle->col = MAXCOL / 2;
//     turtle->row = MAXROW / 2;
//     turtle->angle = 0; //Fcing North?
//     turtle->distance = 0; //alreaddy calloc?
// }


char Ltr(void){
    //no - have to use %lf
    static char start = 'A';
    if(start > 'Z'){
        ERROR("All variable LTR's have been used.");
    }
    return start++;
}

bool Prog(Program *turtle) {
    turtle->endReached = false;
    //Prog done
    while (turtle->cw < MAXCMND - 1 && !turtle->endReached){
        turtle->cw++;
        if (scanf("%s", turtle->cmnd[turtle->cw]) != 1){
            ERROR("Failed to read command.\n");
            return false;
        }
        Inslst(turtle);
    }
    return true;
}

bool Inslst(Program *turtle){
    if(strsame(turtle->cmnd[turtle->cw], "END")){
        turtle->endReached = true;
        return true;
    }
    if(!Ins(turtle)){
        ERROR("Failed.\n");
        return false;
    }
    turtle->cw++;
    // return Inslst(turtle);
}

// bool Ins(Program *turtle){
//     if (strsame(turtle->cmnd[turtle->cw], "FORWARD")){
//         turtle->cw++; // Move to the value after FORWARD
//         if (!Fwd(turtle)){
//             ERROR("Forward did not execute!");
//             return false;
//         }
//         return true;
//     }
//     else if (strsame(turtle->cmnd[turtle->cw], "RIGHT")){
//         turtle->cw++; // Move to the value after RIGHT
//         if (!Rgt(turtle)){
//             ERROR("Right did not execute!");
//             return false;
//         }
//         return true;    
//     }
//     ERROR("Unrecognized instruction!\n");
//     return false;
// }

//also conducting horizontal/vertical?
// bool Fwd(Program *turtle){
    //strlen - 1
    // if (!Num(turtle)){
    //     ERROR("Invalid number after FORWARD");
    //     return false;
    // }
    //How do we actually make it go forward??
    //SOH CAH TOA
    // double radians = turtle->angle * PI / STRAIGHT_ANGLE;
    // turtle->row += turtle->distance * cos(radians);
    // turtle->col += turtle->distance * sin(radians);
    
//     return true;
// }

// bool Num(Program *turtle){
//     if (sscanf("%lf",turtle->cmnd[turtle->cw]) != 1){
//         ERROR("Invalid number input!");
//         return false;
//     }
//     return true;
// }

// bool Rgt(Program *turtle){
//     //Make angles between 0->360
//     while (turtle->angle >= 360) turtle->angle -= 360;
//     while (turtle->angle < 0) turtle->angle += 360;

//     return true;
//     double var;
//     if (sscanf(turtle->cmnd[turtle->cw], "%lf", &var) != 1){
//         ERROR("Invalid number after RIGHT");
//         return false;   
//     }
//     //how can we make go right? Conversion?
//     return true;
// }

// void test(void){
//     //Prog Function Test;
//     Program* testTurtle = (Program*)calloc(1, sizeof(Program));
//     if (!testTurtle){
//         ERROR("Turtle Tests failed to initialise!\n");
//     }

//     strcpy(testTurtle->cmnd[0], "START");
//     testTurtle->cw = 0;
//     assert(Prog(testTurtle) == true);

    // //End Function Test:
    // strcpy(testTurtle->cmnd[1], "END");
    // testTurtle->cw = 1;
    // assert(Inslst(testTurtle) == true);
    // assert(testTurtle->cw == 1);

    // //Testing Forward:
    // strcpy(testTurtle->cmnd[0], "FORWARD");
    // strcpy(testTurtle->cmnd[1], "10");
    // strcpy(testTurtle->cmnd[2], "END");
    // testTurtle->cw = 2; //or 3? 
    // assert(Ins(testTurtle) == true);

    // //Test for Right:
    // strcpy(testTurtle->cmnd[0], "RIGHT");
    // strcpy(testTurtle->cmnd[1], "90");
    // //is it still End for 2?
    // testTurtle->cw = 2;
    // assert(Ins(testTurtle) == true);

//     free(testTurtle);

// }
