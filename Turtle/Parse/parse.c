#include "parse.h"

int main(int argc, char* argv[]){
    test();

    validArgs(argc);
    FILE* fttl = openFile(argv[1]);
    Program* turtle = initTurtle();
    readWords(fttl, turtle);
    runProgram(turtle);

    puts("\nPassed Ok.");
    fclose(fttl);
    free(turtle);
    return 0;
}

void validArgs(int argc){
    if(argc != 2){
        ERROR("Error on argv[0]\n");
        exit(EXIT_FAILURE);
    }
}

FILE* openFile(char* filename){
    FILE* fttl = fopen(filename, "r");
    if(!fttl){
        ERROR("Cannot read from argv[1] \n");
        fclose(fttl);
        exit(EXIT_FAILURE);
    }
    return fttl;
}

Program* initTurtle(void){
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    return turtle;
}

void readWords(FILE* fttl, Program* turtle){
    int i = 0;
    while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
        i++;
    }
}

void runProgram(Program* turtle){
    if(!Prog(turtle)){
        ERROR("Grammar mistakes found in ttl ~ terminated.");
    }
}

bool Prog(Program *turtle){
    if (!strsame(turtle->wds[turtle->cw], "START")){
        NOEXIT_ERROR("No 'START' statement!");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Inslst(Program *turtle){
    turtle->endReached = false; //TODO should i move to prog?
    if(strsame(turtle->wds[turtle->cw], "END")){
        turtle->endReached = true;
        return true;
    }
    if(!Ins(turtle)){
        NOEXIT_ERROR("No 'END' or Unknown Command!");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Ins(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (strsame(cmnd, "FORWARD")){ //TODO this is repeated in Fwd
        return Fwd(turtle);
    } 
    else if (strsame(cmnd, "RIGHT")){
        return Rgt(turtle);
    } 
    return false;
}

bool Fwd(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "FORWARD")){
        NOEXIT_ERROR("Forward did not execute!");
        return false;
    }
    else{
        turtle->cw++;
        double num;
        if(!Num(turtle, &num)){
            NOEXIT_ERROR("Wrong integer input.");
            return false;
        }
    }
    return true;
}

bool Rgt(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "RIGHT")){
        NOEXIT_ERROR("Forward did not execute!\n");
        return false;
    }
    else{
        turtle->cw++;
        double num;
        if(!Num(turtle, &num)){
            NOEXIT_ERROR("Wrong integer input.");
            return false;
        }
    }
    return true;
}

bool Num(Program *turtle, double *num){
    char *number = turtle->wds[turtle->cw];
    char *endptr;

    *num = strtod(number, &endptr);
    if (*endptr == '\0'){
        return true;
    }
    else{
        NOEXIT_ERROR("Invalid Number.");
        return false;
    }
}

bool Var(Program *turtle){
    char* var = turtle->wds[turtle->cw];
    if (strlen(var) != 2) {
        NOEXIT_ERROR("Invalid Variable Input!");
        return false;
    }
    if (var[0] == '$' && Ltr(var[1])){
        return true;
    }
    NOEXIT_ERROR("Invalid Variable Input!");
    return false;
}

bool Ltr(char var){
    if (var >= 'A' && var <= 'Z'){
        return true;
    }
    NOEXIT_ERROR("Invalid Letter Input!");
    return false;
}

void test(void){
    Program* testTurtle = initTurtle();
    //Testing for Error msg [Start]: ~working
    strcpy(testTurtle->wds[0], "END");
    testTurtle->cw = 0;
    assert(Prog(testTurtle) == false);
    // runProgram(testTurtle);
    //Expecting Fatal Error No 'START' statement! occurred in Parse/parse.c, line 59 
    //Uncomment runProgram - expecting Fatal Error Grammar mistakes found in ttl ~ terminated. occurred in Parse/parse.c, line 53

    //Testing for Error msg [End]
    printf("\n");
    strcpy(testTurtle->wds[0], "START");
    strcpy(testTurtle->wds[1], "FINISH");
    testTurtle->cw = 0;
    assert(Prog(testTurtle) == false);
    // runProgram(testTurtle);
    //Expecting: Fatal Error No 'END' or Unknown Command! occurred in Parse/parse.c, line 73

    //Testing for End ~working
    strcpy(testTurtle->wds[0], "START");
    strcpy(testTurtle->wds[1], "END");
    testTurtle->cw = 0;
    runProgram(testTurtle);
    // assert(Prog(testTurtle) == true);

    //Testing that return false if no End - working
    printf("\n");
    strcpy(testTurtle->wds[1], "RIGHT");
    strcpy(testTurtle->wds[2], "45");
    strcpy(testTurtle->wds[3], "FORWARD");
    strcpy(testTurtle->wds[4], "20");
    testTurtle->cw = 0;
    //Expecting no Error msg:
    assert(Ins(testTurtle) == false);
    //Expecting Fatal Error No 'END' or Unknown Command! occurred in Parse/parse.c, line 73
    assert(Prog(testTurtle) == false);

    //Expecting no Error msg:
    strcpy(testTurtle->wds[5], "END");
    testTurtle->cw = 0;
    runProgram(testTurtle);

    // Testing Inslst function - even though no START
    strcpy(testTurtle->wds[0], "FORWARD");
    strcpy(testTurtle->wds[1], "10");
    strcpy(testTurtle->wds[2], "END");
    testTurtle->cw = 0;
    assert(Inslst(testTurtle) == true);

    // Testing Ins function with FORWARD
    strcpy(testTurtle->wds[0], "FORWARD");
    strcpy(testTurtle->wds[1], "10");
    testTurtle->cw = 0;
    assert(Ins(testTurtle) == true);

    // Testing Rgt function
    strcpy(testTurtle->wds[0], "RIGHT");
    strcpy(testTurtle->wds[1], "90");
    testTurtle->cw = 0;
    assert(Rgt(testTurtle) == true);

    // Testing Num function with valid number
    strcpy(testTurtle->wds[0], "10");
    testTurtle->cw = 0;
    double num;
    assert(Num(testTurtle, &num) == true);

    // Testing Num error msg ~ working
    printf("\n");
    strcpy(testTurtle->wds[0], "abc");
    testTurtle->cw = 0;
    assert(Num(testTurtle, &num) == false);
    //Expecting msg: Fatal Error Invalid Number. occurred in Parse/parse.c, line 134 
    
    //Testing for Ltr Function:
    assert(Ltr('A') == true);
    assert(Ltr('Z') == true);
    assert(Ltr('M') == true);
    printf("\n");
    assert(Ltr('a') == false);
    printf("\n");
    assert(Ltr('z') == false);
    printf("\n");
    assert(Ltr('1') == false);
    printf("\n");
    assert(Ltr('@') == false);

    //Test for Var Function:
    // Test 1: Valid variable
    strcpy(testTurtle->wds[0], "$A");
    testTurtle->cw = 0;
    assert(Var(testTurtle) == true);

    // Test 2: Invalid variable (length is not 2)
    strcpy(testTurtle->wds[0], "$AB");
    testTurtle->cw = 0;
    printf("\n");
    assert(Var(testTurtle) == false);

    // Test 3: Invalid variable (first character is not $)
    strcpy(testTurtle->wds[0], "A");
    testTurtle->cw = 0;
    printf("\n");
    assert(Var(testTurtle) == false);

    // Test 4: Invalid variable (second character is not an uppercase letter)
    strcpy(testTurtle->wds[0], "$a");
    testTurtle->cw = 0;
    printf("\n");
    assert(Var(testTurtle) == false);

    // Test 5: Valid letter
    assert(Ltr('A') == true);

    // Test 6: Invalid letter (not an uppercase letter)
    printf("\n");
    assert(Ltr('a') == false);

    free(testTurtle);
}