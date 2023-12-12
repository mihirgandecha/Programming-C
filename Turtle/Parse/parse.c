#include "parse.h"

int main(void) {
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (turtle == NULL){
        ERROR("Turtle failed to initialise!\n");
        return false;
    }
    if (!TurtleInit(turtle)){
        ERROR("Failed to Go to TurtleInit!\n");
        return 1; 
    }
    test();
    return 0;
}

bool TurtleInit(Program *turtle){
    //Need to INIT FUNC: while there is a user input that starts with "START" -> calloc space
    //Take the input
    int input = 0;
    printf("Enter Turtle Commands:\n");
    //How can I free memory if there is no input?
    while(scanf("%s", turtle->wds[input]) == 1 && input >= MAXCMND){
        input++;
    }
    if(!Start(turtle)){
        ERROR("Algorithm failed to start\n");
        return false;
    }
    printf("Parsed OK\n");
    return turtle;
}

bool Start(Program *turtle){
    if(!strsame(turtle->wds[turtle->cw], "START")){
        ERROR("No 'START' statement!\n");
        return false;
    }
    turtle->cw += 1;
    Inslst(turtle);
    return true;
}

bool Inslst(Program *turtle){
    if(strsame(turtle->wds[turtle->cw], "END")){
        return true;
    }
    while(!strsame(turtle->wds[turtle->cw], "END")){
        if(!Ins(turtle)){
            ERROR("Program failed to pass to Instruction Function.\n");
            return false;
        }
        turtle->cw += 1;
    }
    return true;
}


bool Ins(Program *turtle){
    if (strncmp(turtle->wds[turtle->cw], "FORWARD", 7)){
        turtle->cw += 1;
        if(!Fwd(turtle)){
            ERROR("Forward did not execute!");
            return false;
        }
        return true;
    }
    else if(strncmp(turtle->wds[turtle->cw], "RIGHT", 5)){
        turtle->cw += 1; //is this a double?
        if(!Rgt(turtle)){
            ERROR("Right did not execute!");
            return false;
        }    
    }
    ERROR("Instructions failed!");
    return false;
}

bool Fwd(Program *turtle){
    double var; //temporary
    if (sscanf(turtle->wds[turtle->cw], "%lf", &var) != 1){
        ERROR("Invalid number after FORWARD");
        return false;
    }
    //How does forward work??
    return true;
}

bool Rgt(Program *turtle) {
    double var;
    if (sscanf(turtle->wds[turtle->cw], "%lf", &var) != 1) {
        ERROR("Invalid number after RIGHT");
        return false;
    }
    //how can we make go right? Conversion?
    return true;
}

void test(void){
    //Start Function Test;
    Program testTurtle;
    TurtleInit(&testTurtle);
    strcpy(testTurtle.wds[0], "START");
    testTurtle.cw = 0;
    assert(Start(&testTurtle) == true);

    //End Function Test:
    strcpy(testTurtle.wds[1], "END");
    testTurtle.cw = 1;
    assert(Inslst(&testTurtle) == true);
    assert(testTurtle.cw == 2);

    //Testing Forward:
    strcpy(testTurtle.wds[0], "FORWARD");
    strcpy(testTurtle.wds[1], "10");
    strcpy(testTurtle.wds[2], "END");
    testTurtle.cw = 2; //or 3? 
    assert(Ins(&testTurtle) == true);

    //Test for Right:
    strcpy(testTurtle.wds[0], "RIGHT");
    strcpy(testTurtle.wds[1], "90");
    //is it still End for 2?
    testTurtle.cw = 2;
    assert(Ins(&testTurtle) == true);

}
