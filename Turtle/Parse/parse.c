#include "parse.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        ERROR("Error on argv[0]\n");
        exit(EXIT_FAILURE);
    }
    FILE* fttl = fopen(argv[1], "r");
    if(!fttl){
        ERROR("Cannot read from argv[1] \n");
        fclose(fttl);
        exit(EXIT_FAILURE);
    }
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        fclose(fttl);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
        i++;
    }
    // printf("%s\n", turtle->wds[turtle->cw]);
    // printf("%d\n", turtle->cw);
    if(!Prog(turtle)){
        ERROR("Prog did not work");
        return 1;
    }
    puts("OK dokey");
    fclose(fttl);
    free(turtle);
    // test();
    return 0;
}

bool Prog(Program *turtle){
    if (!strsame(turtle->wds[turtle->cw], "START")){
        ERROR("No 'START' statement!\n");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Inslst(Program *turtle){
    turtle->endReached = false;
    if(strsame(turtle->wds[turtle->cw], "END")){
        turtle->endReached = true;
        return true;
    }
    if(!Ins(turtle)){
        ERROR("Failed.\n");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Ins(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];

    if (strsame(cmnd, "FORWARD")){
        return Fwd(turtle);
    } 
    else if (strsame(cmnd, "RIGHT")){
        return Rgt(turtle);
    } 
    else{
        ERROR("Unknown command.\n");
        return false;
    }
}

bool Fwd(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "FORWARD")){
        ERROR("Forward did not execute!\n");
        return false;
    }
    else{
        turtle->cw++;
        double num;
        if(!Num(turtle, &num)){
            ERROR("Wrong integer input.\n");
            return false;
        }
    }
    return true;
}

bool Rgt(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!strsame(cmnd, "RIGHT")){
        ERROR("Forward did not execute!\n");
        return false;
    }
    else{
        turtle->cw++;
        double num;
        if(!Num(turtle, &num)){
            ERROR("Wrong integer input.\n");
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
        ERROR("Invalid Number\n");
        return false;
    }
}

void test(void){
    //Prog Function Test;
    Program* testTurtle = (Program*)calloc(1, sizeof(Program));
    if (!testTurtle){
        ERROR("Turtle Tests failed to initialise!\n");
    }

    //Testing for Start
    testTurtle->cw = 0;
    strcpy(testTurtle->wds[testTurtle->cw], "START");
    assert(Prog(testTurtle) == true);

    // //Testing for End:
    testTurtle->cw = 1;
    strcpy(testTurtle->wds[testTurtle->cw], "END");
    assert(Inslst(testTurtle) == true);

    // //Testing for Ins
    // strcpy(testTurtle->wds[2], "FORWARD");
    // strcpy(testTurtle->wds[3], "10");
    // testTurtle->cw = 2;
    // assert(Ins(testTurtle) == true);

    // //Testing for Fwd
    // strcpy(testTurtle->wds[2], "FORWARD");
    // strcpy(testTurtle->wds[3], "10");
    // testTurtle->cw = 2;
    // assert(Fwd(testTurtle) == true);

    // //Testing for Rgt
    // strcpy(testTurtle->wds[2], "RIGHT");
    // strcpy(testTurtle->wds[3], "10");
    // testTurtle->cw = 2;
    // assert(Rgt(testTurtle) == true);

    // //Testing for Num
    // strcpy(testTurtle->wds[2], "10");
    // testTurtle->cw = 2;
    // double num;
    // assert(Num(testTurtle, &num) == true);

    free(testTurtle);
}