#include "interp.h"
#include "../neillsimplescreen.h"

int main(int argc, char* argv[]){
    // printf("%d", argc);
    // testBresenham();
    // return 0;

    validArgs(argc);
    FILE* fttl = openFile(argv[1]);
    // if (argv[2] then output to screen
    // FILE* fttx = openFile(argv[2]);

    Program* turtle = initTurtle();
    initScrn(turtle);
    readWords(fttl, turtle);
    runProgram(turtle);
    printtoscreen(turtle);

    // degToRadTest();
    puts("\nPassed Ok.");
    fclose(fttl);

    free(turtle);
    // test();
    // return 0;
    return 0;
}

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
//iso error
void printtoscreen(Program *turtle){
    neillclrscrn();
    neillbgcol(black);
    neillcursorhome();
    // double seconds =;
    puts("\n");
    puts("\n");
    puts("\n");
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            printf("%c", turtle->SCREEN[row][col]);
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
    turtle->rAngle = 0;
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
            //should this just be function parameter?
            turtle->distance = atof(turtle->wds[turtle->cw]);
            intFwd(turtle);
        }
    }
    // printtoscreen(turtle);
    return true;
}

//use line algorithm - getpoint
//pass in start point (current turtle pos - not midpoint!), pass distance 

bool intFwd(Program *turtle){
    if((turtle->distance > 0 && turtle->distance > COL) || (turtle->distance < 0 && turtle->distance < -COL)){
        return false;
    }
    //TODO check if negative:
    int prevCol = (int)turtle->col;
    int prevRow = (int)turtle->row;
    
    int dRow = round(cos(turtle->rAngle) * -turtle->distance);
    int dCol = round(sin(turtle->rAngle) * turtle->distance); 
    //(if not postscript) -> store (start + delta)
    turtle->colour = 'W';
    int newRow = prevRow + dRow;
    int newCol = prevCol + dCol;
    if(Bresenham(turtle, prevRow, prevCol, newRow, newCol, dRow, dCol)){
        turtle->row = newRow;
        turtle->col = newCol;
        return true;
    }
    return false;
}    

bool Bresenham(Program *turtle, int rowStart, int colStart, int rowEnd, int colEnd, int dRow, int dCol){
    int signRow = rowStart < rowEnd ? 1 : -1;
    int signCol = colStart < colEnd ? 1 : -1;
    dRow = abs(dRow);
    dCol = abs(dCol);
    int error = dCol - dRow;
    //can i have boundry check in another func?s
    if(rowStart >= 0 && rowStart < ROW && colStart >= 0 && colStart < COL){
        turtle->SCREEN[rowStart][colStart] = turtle->colour;
    }
    while(abs(rowStart - rowEnd) > 1 || abs(colStart - colEnd) > 1){
        //calculate if error for next point
        int doubleError = 2 * error;
        if(doubleError >= -dRow){
            error -= dRow;
            colStart += signCol;
        }
        if(doubleError <= dCol){
            error += dCol;
            rowStart += signRow;
        }
        if(rowStart >= 0 && rowStart < ROW && colStart >= 0 && colStart < COL){
            turtle->SCREEN[rowStart][colStart] = turtle->colour;
        }
    }
    return true;
}



void testBresenham(void){
    Program *testTurtle = initTurtle();
    testTurtle->col = SCOL;
    testTurtle->row = SROW;
    testTurtle->rAngle = 0;
    initScrn(testTurtle);

    //test for FWD 5
    testTurtle->cw = 0;
    char* cmnd = "FORWARD";
    strcpy(testTurtle->wds[testTurtle->cw], cmnd); 
    testTurtle->cw = 1;
    char* cmnd2 = "5";
    strcpy(testTurtle->wds[testTurtle->cw], cmnd2); 
    testTurtle->cw = 0;
    Fwd(testTurtle);
    assert(testTurtle->SCREEN[SROW][SCOL] == 'W');
    assert(testTurtle->SCREEN[SROW][SCOL] == 'W');
    assert(testTurtle->SCREEN[SROW][SCOL] == 'W');
    assert(testTurtle->SCREEN[SROW][SCOL] == 'W');
    assert(testTurtle->SCREEN[SROW][SCOL] == 'W');
    free(testTurtle);
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
            //just store radians
            double angle = atof(turtle->wds[turtle->cw]);
            turtle->rAngle = turtle->rAngle + degToRad(angle);
        }
    }
    return true;
}

double degToRad(double degrees){
    degrees = fabs(degrees);
    if(degrees > FULLCIRC){
        degrees = fmod(degrees, FULLCIRC);
    }
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
    // setCol(turtle, turtle->wds[turtle->cw]);
    return true;
}

void setCol(Program *turtle, char* colour){
//TODO is function len > 20 ok? 
//TODO need to change background 
    //change the background
    if (STRSAME(colour, "BLACK")){
        turtle->colour = 'B';
    } 
    else if (STRSAME(colour, "WHITE")){
        turtle->colour = 'W';
    } 
    else if (STRSAME(colour, "RED")){
        turtle->colour = 'R';
    } 
    else if (STRSAME(colour, "GREEN")){
        turtle->colour = 'G';
    } 
    else if (STRSAME(colour, "BLUE")){
        turtle->colour = 'B';
    } 
    else if (STRSAME(colour, "YELLOW")){
        turtle->colour = 'Y';
    } 
    else if (STRSAME(colour, "CYAN")){
        turtle->colour = 'C';
    } 
    else if (STRSAME(colour, "MAGENTA")){
        turtle->colour = 'M';
    } 
    else {
        turtle->colour = 'W';
    }
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
