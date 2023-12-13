#include "parse.h"

int main(void){
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        return 1;
    }
    if(!Start(turtle)){
        ERROR("Algorithm failed to start\n");
        return 1;
    }
    test();
    printf("Parsed OK\n");
    free(turtle);
    return 0;
}

bool Start(Program *turtle){
    turtle->cw = 0;
    printf("Enter Turtle Commands:\n");
    while(scanf("%s", turtle->cmnd[turtle->cw]) == 1 && turtle->cw >= MAXCMND){
        if(!strsame(turtle->cmnd[turtle->cw], "START")){
        ERROR("No 'START' statement!\n");
        return false;
        }
        turtle->cw++;
        Inslst(turtle);
    }
    return true;
}

bool Inslst(Program *turtle){
    if(strsame(turtle->cmnd[turtle->cw], "END")){
        return true;
    }
    while(!strsame(turtle->cmnd[turtle->cw], "END")){
        if(!Ins(turtle)){
            ERROR("Program failed to pass to Instruction Function.\n");
            return false;
        }
        turtle->cw += 1;
    }
    return true;
}

bool Ins(Program *turtle){
    if (strsame(turtle->cmnd[turtle->cw], "FORWARD")){
        turtle->cw += 1;
        if(!Fwd(turtle)){
            ERROR("Forward did not execute!");
            return false;
        }
        return true;
    }
    else if(strsame(turtle->cmnd[turtle->cw], "RIGHT")){
        turtle->cw += 1; //is this a double?
        if(!Rgt(turtle)){
            ERROR("Right did not execute!");
            return false;
        }
        return true;    
    }
    else{
        return Inslst(turtle);
    }
    ERROR("Instructions failed!");
    return false;
}
//also conducting horizontal/vertical?
bool Fwd(Program *turtle){
    double num;
    if (!Num(turtle, &num)){
        ERROR("Invalid number after FORWARD");
        return false;
    }
    // if (sscanf(turtle->cmnd[turtle->cw], "%ld", num) != 1) {
    //     ERROR("Invalid number input!");
    //     return false;
    // }
    // if (sscanf("%s", turtle->cmnd[turtle->cw]) && Num(num) != 1){
    //     ERROR("Invalid number after FORWARD");
    //     return false;
    // }
    //How do we actually make it go forward??
    return true;
}

bool Num(Program *turtle, double *Num){
    if (sscanf(turtle->cmnd[turtle->cw], "%lf", Num) != 1) {
        ERROR("Invalid number input!");
        return false;
    }
    return true;
}

bool Rgt(Program *turtle){
    double var;
    if (sscanf(turtle->cmnd[turtle->cw], "%lf", &var) != 1){
        ERROR("Invalid number after RIGHT");
        return false;   
    }
    //how can we make go right? Conversion?
    return true;
}


void test(void){
    //Start Function Test;
    Program* testTurtle = (Program*)calloc(1, sizeof(Program));
    if (!testTurtle){
        ERROR("Turtle Tests failed to initialise!\n");
    }

    strcpy(testTurtle->cmnd[0], "START");
    testTurtle->cw = 0;
    assert(Start(testTurtle) == true);

    //End Function Test:
    strcpy(testTurtle->cmnd[1], "END");
    testTurtle->cw = 1;
    assert(Inslst(testTurtle) == true);
    assert(testTurtle->cw == 1);

    //Testing Forward:
    strcpy(testTurtle->cmnd[0], "FORWARD");
    strcpy(testTurtle->cmnd[1], "10");
    strcpy(testTurtle->cmnd[2], "END");
    testTurtle->cw = 2; //or 3? 
    assert(Ins(testTurtle) == true);

    //Test for Right:
    strcpy(testTurtle->cmnd[0], "RIGHT");
    strcpy(testTurtle->cmnd[1], "90");
    //is it still End for 2?
    testTurtle->cw = 2;
    assert(Ins(testTurtle) == true);

    free(testTurtle);

}
