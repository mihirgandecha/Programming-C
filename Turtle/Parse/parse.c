#include "parse.h"

int main(int argc, char* argv[]){
    test();
    return 0;

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
    else if (strsame(cmnd, "COLOUR")){
        return Col(turtle);
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
        NOEXIT_ERROR("COLOUR was not registered.");
        return false;
    }
    turtle->cw++;
    if(!Var(turtle) && !Word(turtle)){
        return false;
    }
    return true;
}

bool Loop(Program *turtle){
    if (!strsame(turtle->wds[turtle->cw], "LOOP")){
        return false;
    }
    turtle->cw++;
    if (!Ltr(*turtle->wds[turtle->cw])){
        return false;
    }
    turtle->cw++;
    if (!strsame(turtle->wds[turtle->cw], "OVER")){
        return false;
    }
    turtle->cw++;
    if (!Lst(turtle)){
        return false;
    }
    if (!Inslst(turtle)){
        return false;
    }
    return true;
}

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

bool Word(Program* turtle){
    char* word = turtle->wds[turtle->cw];
    int len = strlen(word);
    if(word[0] == '"' && word[len - 1] == '"'){
        return true;
    }
    return false;
}

bool Item(Program* turtle){
    if(!Varnum(turtle) && !Word(turtle)){
        return false;
    }
    return true;
}

bool Items(Program* turtle){
    if(strsame(turtle->wds[turtle->cw], "}")){
        turtle->cw++;
        return true;
    }
    else if(Item(turtle)){
        turtle->cw++;
        return Items(turtle);
    }
    return false;
}

bool Lst(Program* turtle){
    if(strsame(turtle->wds[turtle->cw], "{")){
        turtle->cw++;
        return Items(turtle);
    }
    return false;
}

bool Op(Program* turtle){
    //TODO shall i be testing NULL for all functions?
    if(!turtle || !turtle->wds || !turtle->wds[turtle->cw]){
        return false;
    }
    if(strlen(turtle->wds[turtle->cw]) != 1){
        return false;
    }
    switch(turtle->wds[turtle->cw][0]){
        case '+':
        case '-':
        case '/':
        case '*':
            return true;
        default:
            return false;
    }
}
//<PFIX>::= ")" | <OP> <PFIX> | <VARNUM> <PFIX>
bool Pfix(Program* turtle){
    if(strsame(turtle->wds[turtle->cw], ")")){
        turtle->cw++;
        return true;
    }
    else if (Op(turtle)){
        turtle->cw++;
        return Pfix(turtle);
    }
    else if (Varnum(turtle)){
        turtle->cw++;
        return Pfix(turtle);
    }
    return false;
}

