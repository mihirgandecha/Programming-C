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
    NOEXIT_ERROR("No 'FWD' OR 'Rgt' function."); 
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
        if(!Varnum(turtle)){
            return false;
        }
    }
    return true;
}

bool Rgt(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "RIGHT")){
        NOEXIT_ERROR("Right did not execute!");
        return false;
    }
    else{
        turtle->cw++;
        if(!Varnum(turtle)){
            return false;
        }
    }
    return true;
}

bool Col(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "COLOUR")){
        NOEXIT_ERROR("Colour was not registered.");
        return false;
    }
    turtle->cw++;
    if(!Var(turtle)){
        return false;
        // if(!Word(turtle)){
        //     return false;
        // }
    }
    return true;
}

// bool Word()

bool Varnum(Program *turtle){
    if(!Var(turtle)){
        if(!Num(turtle)){
            NOEXIT_ERROR("Invalid Number or Variable Name.");
            return false;
        }
    }
    return true; 
}

bool Num(Program *turtle){
    char *number = turtle->wds[turtle->cw];
    char *endptr;
    strtod(number, &endptr);
    if (*endptr == '\0'){
        return true;
    }
    else{
        return false;
    }
}

bool Var(Program *turtle){
    char* var = turtle->wds[turtle->cw];
    if (strlen(var) != 2) {
        return false;
    }
    if (var[0] == '$' && Ltr(var[1])){
        return true;
    }
    return false;
}

bool Ltr(char var){
    if (var >= 'A' && var <= 'Z'){
        return true;
    }
    return false;
}

// bool Word(Program* turtle){
//     char word = turtle.wds[turtle->cw];
//     int len = strlen(*word);
//     if(word[0] == '"' && word[len - 1] == '"'){
//         return true;
//     }
//     return false;
// }

// void test(void){
//     Program* testTurtle = initTurtle();
//     //Testing for Error msg [Start]: ~working
//     strcpy(testTurtle->wds[0], "END");
//     testTurtle->cw = 0;
//     puts("\nTest of <Prog> error msg:");
//     assert(Prog(testTurtle) == false);
//     // runProgram(testTurtle);
//     //Expecting Fatal Error No 'START' statement! occurred in Parse/parse.c, line 59 
//     //Uncomment runProgram - expecting Fatal Error Grammar mistakes found in ttl ~ terminated. occurred in Parse/parse.c, line 53

//     //Testing for Error msg [End]
//     strcpy(testTurtle->wds[0], "START");
//     strcpy(testTurtle->wds[1], "FINISH");
//     testTurtle->cw = 0;
//     puts("\nTest of <Prog> error msg:");
//     assert(Prog(testTurtle) == false);
//     // runProgram(testTurtle);
//     //Expecting: Fatal Error No 'END' or Unknown Command! occurred in Parse/parse.c, line 73

//     //Testing for End ~working
//     strcpy(testTurtle->wds[0], "START");
//     strcpy(testTurtle->wds[1], "END");
//     testTurtle->cw = 0;
//     runProgram(testTurtle);
//     // assert(Prog(testTurtle) == true);

//     //Testing that return false if no End - working
//     strcpy(testTurtle->wds[1], "RIGHT");
//     strcpy(testTurtle->wds[2], "45");
//     strcpy(testTurtle->wds[3], "FORWARD");
//     strcpy(testTurtle->wds[4], "20");
//     testTurtle->cw = 0;
//     //Expecting no Error msg:
//     puts("\nTest of <Ins> error msg:");
//     assert(Ins(testTurtle) == false);
//     //Expecting Fatal Error No 'END' or Unknown Command! occurred in Parse/parse.c, line 73
//     puts("\nTest 4 of <Prog> error msg:");
//     assert(Prog(testTurtle) == false);

//     //Expecting no Error msg:
//     strcpy(testTurtle->wds[5], "END");
//     testTurtle->cw = 0;
//     runProgram(testTurtle);

//     // Testing Inslst function - even though no START
//     strcpy(testTurtle->wds[0], "FORWARD");
//     strcpy(testTurtle->wds[1], "10");
//     strcpy(testTurtle->wds[2], "END");
//     testTurtle->cw = 0;
//     assert(Inslst(testTurtle) == true);

//     // Testing Ins function with FORWARD
//     strcpy(testTurtle->wds[0], "FORWARD");
//     strcpy(testTurtle->wds[1], "10");
//     testTurtle->cw = 0;
//     assert(Ins(testTurtle) == true);

//     // Testing Rgt function
//     strcpy(testTurtle->wds[0], "RIGHT");
//     strcpy(testTurtle->wds[1], "90");
//     testTurtle->cw = 0;
//     assert(Rgt(testTurtle) == true);

//     // Testing Num function with valid number
//     strcpy(testTurtle->wds[0], "10");
//     testTurtle->cw = 0;
//     assert(Num(testTurtle) == true);

//     // Testing Num error msg ~ working
//     strcpy(testTurtle->wds[0], "abc");
//     testTurtle->cw = 0;
//     puts("\nTest 1 of <Num> error msg:");
//     assert(Num(testTurtle) == false);
//     //Expecting msg: Fatal Error Invalid Number. occurred in Parse/parse.c, line 134 
    
//     //Testing for Ltr Function:
//     assert(Ltr('A') == true);
//     assert(Ltr('Z') == true);
//     assert(Ltr('M') == true);
//     puts("\nTest 4 of <Ltr> error msg:");
//     assert(Ltr('a') == false);
//     puts("\nTest 5 of <Ltr> error msg:");
//     assert(Ltr('z') == false);
//     puts("\nTest 6 of <Ltr> error msg:");
//     assert(Ltr('1') == false);
//     puts("\nTest 7 of <Ltr> error msg:");
//     assert(Ltr('@') == false);

//     //Test for Var Function:
//     // Test 1: Valid variable
//     strcpy(testTurtle->wds[0], "$A");
//     testTurtle->cw = 0;
//     assert(Var(testTurtle) == true);
//     // Test 2: Invalid variable (length is not 2)
//     strcpy(testTurtle->wds[0], "$AB");
//     testTurtle->cw = 0;
//     puts("\nTest 2 of <Var> error msg:");
//     assert(Var(testTurtle) == false);
//     // Test 3: Invalid variable (first character is not $)
//     strcpy(testTurtle->wds[0], "A");
//     testTurtle->cw = 0;
//     puts("\nTest 4 of <Var> error msg:");
//     assert(Var(testTurtle) == false);
//     // Test 4: Invalid variable (second character is not an uppercase letter)
//     strcpy(testTurtle->wds[0], "$a");
//     testTurtle->cw = 0;
//     puts("\nTest 4 of <Var> error msg:");
//     assert(Var(testTurtle) == false);
//     // Test 5: Valid letter
//     assert(Ltr('A') == true);
//     // Test 6: Invalid letter (not an uppercase letter)
//     puts("\nTest 6 of <Var> error msg:");
//     assert(Ltr('a') == false);

//     //Test for <Varnum> Function
//     // Test 1: Valid variable
//     strcpy(testTurtle->wds[0], "$A");
//     testTurtle->cw = 0;
//     assert(Varnum(testTurtle) == true);
//     // Test 2: Valid number
//     strcpy(testTurtle->wds[0], "10");
//     testTurtle->cw = 0;
//     assert(Varnum(testTurtle) == true);
//     // Test 3: Invalid input (not a variable or a number)
//     Program* testTurtle2 = initTurtle();
//     strcpy(testTurtle2->wds[0], "AB");
//     testTurtle2->cw = 0;
//     puts("\nTest 3 of <Varnum> error msg:");
//     assert(Varnum(testTurtle2) == false);

//     //Testing for <COL> function:
//     strcpy(testTurtle2->wds[0], "COLOUR");
//     strcpy(testTurtle2->wds[1], "$A");
//     testTurtle2->cw = 0;
//     assert(Col(testTurtle2) == true);

//     free(testTurtle);
//     free(testTurtle2);
// }