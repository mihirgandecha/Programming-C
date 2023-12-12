#include "parse.h"

int main(void){
    Program turtle;
    TurtleInit(*turtle);
    return 0;
}

bool TurtleInit(Program *turtle){
    //while there is a user input that starts with "START" -> calloc space
    Program* turtle = calloc(1, sizeof(Program));
    if (turtle == NULL){
        return false;
    }
    //Take the input
    int userIn = 0;
    //How can I free memory if there is no input?
    while(scanf("%s", turtle->wds[userIn++] == 1));
    Start(turtle);
    printf("Parsed OK\n");
    return turtle;
}

bool Start(Program *turtle){
    if(!strsame(turtle->wds[turtle->cw], "START")){
        printf("NO START statement ?");
        return false;
    }
    turtle->cw += 1;
    Inslst(turtle);
    return true;
}

bool Inslst(Program *turtle){
    if(strsame(turtle->cw[1] == "END")){
        return true;
    }
    else{
        Ins(turtle);
        turtle->cw += 1;
        Inslst(turtle);
        return true;
    }
    return false;
}

bool Ins(Program *p){
    if(strsame(tur))

}



void test(void){
    //Start Function Test;
    Program testTurtle = TurtleInit();
    testTurtle.wds[0] = "START";
    assert(Start(testTurtle) == true);

    //End Function Test:
    testTurtle.wds[1] = "END";
    assert(Inslst(testTurtle) == true); //should I make a delete function like bsa for testing?


}

