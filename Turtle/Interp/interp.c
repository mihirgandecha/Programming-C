#include "interp.h"
#include "../neillsimplescreen.h"

int main(int argc, char* argv[]){
    // printf("%d", argc);

    validArgs(argc);
    degToRadTest();
    FILE* fttl = openFile(argv[1]);
    //if argv[2] then output to screen
    // FILE* fttx = openFile(argv[2]);

    Program* turtle = initTurtle();
    readWords(fttl, turtle);
    runProgram(turtle);
    initScrn(turtle);
    puts("\nPassed Ok.");
    fclose(fttl);
    free(turtle);

    // test();
    // return 0;
    return 0;
}
//need 2D-arr for Screen and print2screen function

//use fgcol,print char, s

void validArgs(int argc){
    if(argc != EXPECTED_ARGS){
        ERROR("Error on argv[0]\n");
        exit(EXIT_FAILURE);
    }
}

FILE* openFile(char* filename){
    FILE* fttl = fopen(filename, "r");
    if(!fttl){
        ERROR("Cannot read from argv[1] \n");
        fclose(fttl);
        // exit(EXIT_FAILURE);
    }
    return fttl;
}

// FILE* openFileTxt(char* filename){
//     FILE* ftxt = fopen(filename, "r"); //TODO does it need to be write to?
//     if(!fttl){
//         ERROR("Cannot read from argv[1] \n");
//         fclose(fttl);
//         // exit(EXIT_FAILURE);
//     }
//     return fttl;
// }

void initScrn(Program *turtle){
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            turtle->SCREEN[row][col] = ' ';
        }
    }
}

//llop cnt over distane
//call trig
//check in bound of screen
//asign char to screen
//in struct have colour = 'W' default


void printtoscreen(Program *turtle){
    neillclrscrn();
    neillbgcol(black);
    neillcursorhome();
    // double s = 0.5;
    //given we have current pos, and new pos, need to print each step:
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            printf("%c", turtle->SCREEN[col][row]);
        }
        printf("\n");
    }
    //reset after used:
    neillreset();
}

Program* initTurtle(void){
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    initPos(turtle);
    return turtle;
}

void initPos(Program *turtle){
    turtle->col = SCOL;
    turtle->row = SROW;
    turtle->angle = 0;
    turtle->radians = 0;
}

void readWords(FILE* fttl, Program* turtle){
    if(!checkNull(turtle)){
        return;
    }
    int i = 0;
    while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
        i++;
    }
}

void runProgram(Program* turtle){
    turtle->numUsed = false;
    if(!Prog(turtle)){
        ERROR("Grammar mistakes found in ttl.");
    }
}

bool Prog(Program *turtle){
    if (!STRSAME(turtle->wds[turtle->cw], "START")){
        DEBUG("No 'START' statement!");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Inslst(Program *turtle){
    turtle->endReached = false; 
    if(STRSAME(turtle->wds[turtle->cw], "END")){
        turtle->endReached = true;
        return true;
    }
    if(!Ins(turtle)){
        DEBUG("No 'END' or Unknown Command!");
        return false;
    }
    turtle->cw++;
    return Inslst(turtle);
}

bool Ins(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (STRSAME(cmnd, "FORWARD")){ 
        return Fwd(turtle);
    } 
    else if (STRSAME(cmnd, "RIGHT")){
        return Rgt(turtle);
    }
    else if (STRSAME(cmnd, "COLOUR")){
        return Col(turtle);
    }
    else if (STRSAME(cmnd, "LOOP")){
        return Loop(turtle);
    }
    else if (STRSAME(cmnd, "SET")){
        return Set(turtle);
    }
    DEBUG("No 'FWD' OR 'Rgt' OR 'Col' input."); 
    return false;
}

bool Fwd(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!STRSAME(cmnd, "FORWARD")){
        return false;
    }
    else{
        turtle->cw++;
        if(!Varnum(turtle)){
            return false;
        }
        if(Num(turtle)){
            turtle->distance = turtle->distance + atof(turtle->wds[turtle->cw]);
            intFwd(turtle);
            return true;
        }
    }
//interp Fwd func
    return true;
}

void intFwd(Program *turtle){
    //First interpFwd check:
    //fwd can be signed val, cannot be 51? as screen board size?
    if((turtle->distance > 0 && turtle->distance > COL) || (turtle->distance < 0 && turtle->distance < -COL)){
        return;
    }
    //change in row and col then add:
    //call round function, pump in double, then push to col,row
    double dRow = sin(turtle->radians) * turtle->distance;
    double dCol = cos(turtle->radians) * -turtle->distance;
    dRow = round(dRow);
    dCol = round(dCol);

    turtle->row += (int)dRow;
    turtle->col += (int)dCol;
    printtoscreen(turtle);
}    

bool Rgt(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!STRSAME(cmnd, "RIGHT")){
        return false;
    }
    else{
        turtle->cw++;
        if(!Varnum(turtle)){
            return false;
        }
        //interp for num:
        if(Num(turtle)){
            //start with only 1 instruction: ie RIGHT 0, FWD 15
            turtle->angle = turtle->angle + atof(turtle->wds[turtle->cw]);
            turtle->radians = turtle->radians + degToRad(turtle->angle);
        }
    }
    return true;
}

double degToRad(double degrees){
    //Log: 
    //while loop for constantly adding 360 if negative
    //used fmod instead from stk overflow to make degrees within range [0->360]
    //get absolute value (fabs)
    degrees = fabs(degrees);

    if(degrees > FULLCIRC){
        degrees = fmod(degrees, FULLCIRC);
    }
    // if (degrees < 0){
    //     degrees += FULLCIRC;
    // }
    double radians = degrees * (M_PI / HALFCIRC);
    return radians;
}

bool Col(Program *turtle){
    char* cmnd = turtle->wds[turtle->cw];
    if (!STRSAME(cmnd, "COLOUR")){
        return false;
    }
    turtle->cw++;
    if(!Var(turtle) && !Word(turtle)){
        return false;
    }
    return true;
}

bool Loop(Program *turtle){
    if (!STRSAME(turtle->wds[turtle->cw], "LOOP")){
        return false;
    }
    turtle->cw++;
    if (!Ltr(turtle)){
        return false;
    }
    turtle->cw++;
    if (!STRSAME(turtle->wds[turtle->cw], "OVER")){
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

bool Set(Program *turtle){
    if(!STRSAME(turtle->wds[turtle->cw], "SET")){
        DEBUG("Expected 'SET'");
        return false;
    }
    turtle->cw++;
    if(!Ltr(turtle)){
        return false;
    }
    turtle->cw++;
    if(!STRSAME(turtle->wds[turtle->cw], "(")){
        DEBUG("Expected 'Opening '('");
        return false;
    }
    turtle->cw++;
    if(!Pfix(turtle)){
        return false;
    }
    return true; 
}

bool Varnum(Program *turtle){
    if(!Var(turtle) && !Num(turtle)){
        return false;
    }
    return true; 
}

bool Num(Program *turtle){
    char *number = turtle->wds[turtle->cw];
    char *endptr;
    strtod(number, &endptr);
    if (*endptr == '\0'){
        turtle->numUsed = true;
        return true;
    }
    else{
        return false;
    }
}

bool Var(Program *turtle){
    char* var = turtle->wds[turtle->cw];
    if (strlen(var) != EXPECTED_VARLEN) {
        return false;
    }
    if (var[0] == '$' && Ltr(turtle)){
        return true;
    }
    return false;
}

bool Ltr(Program *turtle){
    char* var = turtle->wds[turtle->cw];
    int len = strlen(var);
    if (len == 1){
        char firstChar = var[0];
        if (firstChar >= 'A' && firstChar <= 'Z'){
            return true;
        }
    }
    else if (len > 1){
        char firstChar = var[0];
        char secondChar = var[1];
        if (firstChar == '$' && secondChar >= 'A' && secondChar <= 'Z'){
            return true;
        }
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
    if(STRSAME(turtle->wds[turtle->cw], "}")){
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
    if(STRSAME(turtle->wds[turtle->cw], "{")){
        turtle->cw++;
        return Items(turtle);
    }
    return false;
}

bool checkNull(Program *turtle){
    if(!turtle){
        return false;
    }
    if(!turtle->wds){
        return false;
    }
    if(!turtle->wds[turtle->cw]){
        return false;
    }
    return true;
}

bool Op(Program* turtle){
    if(!checkNull(turtle)){
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

bool Pfix(Program* turtle){
    if(!checkNull(turtle)){
        return false;
    }
    if(STRSAME(turtle->wds[turtle->cw], ")")){
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

void degToRadTest(void){
    //Blackbox testing:
    /*
    //Log:Does not work as testing for floating point
    number does not represent real number
    ^found I needed to use small tolerance
    (1e-12) <- too complex, used a range
    Degrees × (π/180) = Radians
    Radians  × (180/π) = Degrees
    360 Degrees = 2π Radians
    180 Degrees = π Radians
    */
    // Test conversion of 0 degrees
    double result;
    // Test conversion of 0 degrees
    result = degToRad(0);
    assert((int)result == 0);
    // Test conversion of -0 degrees (TODO Edge case - does RIGHT -0 work?)
    result = degToRad(-0);
    assert((int)result == 0);
    // Test conversion of 360 degrees
    result = degToRad(360);
    assert(result >= 6.1 && result <= 6.3);
    // Test conversion of -360 degrees
    result = degToRad(-360);
    assert(result >= 6.1 && result <= 6.3);
    // Test conversion of 90 degrees
    result = degToRad(90);
    assert(result >= 1.3 && result <= 1.6);
    // Test conversion of -90 degrees (testing fabs)
    result = degToRad(-90);
    assert(result >= 1.3 && result <= 1.6);
    // Test conversion of 180 degrees
    result = degToRad(HALFCIRC);
    assert(result >= 3.10 && result <= 3.20);
    // Test conversion of -180 degrees
    result = degToRad(-HALFCIRC);
    assert(result >= 3.10 && result <= 3.20);
    // Test conversion of 270 degrees
    result = degToRad(270);
    assert(result >= 4.70 && result <= 4.80);
    // Test conversion of -270 degrees
    result = degToRad(-270);
    assert(result >= 4.70 && result <= 4.80);
    //Edge cases:
    // .0 <- 
    // test very small +ve degree
    result = degToRad(1e-12);
    assert(result > 0 && result < 1e-12);
    // test very small -ve degree
    result = degToRad(-1e-12);
    assert(result > 0 && result < 1e-12);
    // test very large -ve degree
    result = degToRad(-1e12);
    assert(result >= 0 && result <= 2 * M_PI);
    // test very large +ve degree
    result = degToRad(1e12);
    assert(result >= 0 && result <= 2 * M_PI);
    // test fractional degree
    result = degToRad(0.123456789);
    assert(result > 0 && result < M_PI / 360);
    // test negative fractional degree
    result = degToRad(-0.123456789);
    assert(result > 0 && result < M_PI / 360);
    // test degree slightly less than 360
    result = degToRad(359.999999999);
    assert(result > 0 && result < (2 * M_PI));
    // test degree slightly more than 0
    result = degToRad(0.000000001);
    assert(result > 0 && result < M_PI / 180);
}
