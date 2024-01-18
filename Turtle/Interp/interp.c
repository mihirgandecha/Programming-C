#include "interp.h"
#include "../neillsimplescreen.h"
#include "mintest.h"

int main(int argc, char* argv[]){
    test_subStr();
    test_isWithinBounds();
    validArgs(argc);
    FILE* fttl = openFile(argv[1]);
    Program* turtle = initTurtle();
    initScrn(turtle);
    readWords(fttl, turtle);
    runProgram(turtle);
    if(argc > DOUBLE){
        writeFile(argv[DOUBLE], turtle);
    }
    else{
        printtoscreen(turtle);
    }
    fclose(fttl);
    free(turtle);
    lrun("Is Within Bounds: ", test_isWithinBounds);
    lrun("Basic Test:", test1);
    return 0;
}

void validArgs(int argc){
    if(argc < MIN_ARGS){
        ERROR("Error on argv[0]\n");
        exit(EXIT_FAILURE);
    }
}

FILE* openFile(char* filename){
    FILE* fttl = fopen(filename, "r");
    if(!fttl){
        ERROR("Cannot read from argv[1] \n");
        fclose(fttl);
        //TODO: How am I doing error reporting in interpreter?
        // exit(EXIT_FAILURE);
    }
    return fttl;
}

//TODO: Fix
// Function to write to file
FILE* writeFile(char* filename, Program *turtle){
    //TODO magicnum
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "Turtle/myResults/%s", filename);

    FILE* fttx = fopen(filepath, "w");
    if(!fttx){
        ERROR("Cannot read from argv[2] \n");
        fclose(fttx);
        // exit(EXIT_FAILURE);
    }
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            fprintf(fttx, "%c", turtle->SCREEN[row][col]);
        }
        fprintf(fttx, "\n");
    }
    return fttx;
}

//TODO: Test
Program* initTurtle(void){
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    initPos(turtle);
    return turtle;
}

//TODO: Test + should I put into initTurtle?
void initPos(Program *turtle){
    turtle->col = SCOL;
    turtle->row = SROW;
    turtle->rAngle = 0;
}

//TODO: Test how?
void readWords(FILE* fttl, Program* turtle){
    if(!checkNull(turtle)){
        return;
    }
    int i = 0;
    while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
        i++;
    }
}
//TODO: Test how?
void runProgram(Program* turtle){
    turtle->numUsed = false;
    if(!Prog(turtle)){
        ERROR("Grammar mistakes found in ttl.");
    }
}
//TODO Test
void initScrn(Program *turtle){
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            turtle->SCREEN[row][col] = ' ';
        }
    }
}

//TODO: Format: remove puts?
//TODO: Format: how many seconds delay and in right placement?
void printtoscreen(Program *turtle){
    neillclrscrn();
    neillbgcol(black);
    neillcursorhome();
    double seconds = SCR_DELAY;
    puts("\n");
    puts("\n");
    puts("\n");
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            printf("%c", turtle->SCREEN[row][col]);
        }
        //TODO Check if placement correct:
        neillbusywait(seconds);
        printf("\n");
    }
    neillreset();
}

/*
------------------------------------------------------------PARSER/INTERPRETER STARTS HERE----------------------------------------------------------------------------
*/

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
            turtle->distance = atof(turtle->wds[turtle->cw]);
            intFwd(turtle);
        }
    }
    return true;
}

//TODO remove after
void test1() {
    lok('a' == 'a');
}

bool intFwd(Program *turtle){
    //TODO: Split into small functions.
    //TODO: Func1 - if distance in bound, do I need? Does FWD 0 interpret?
    if((turtle->distance > 0 && turtle->distance > COL) || (turtle->distance < 0 && turtle->distance < -COL)){
        return false;
    }
    int prevCol = (int)turtle->col;
    int prevRow = (int)turtle->row;
    //TODO: Func2 - trig calculations, combine with calculating newRow, newCol
    int dRow = round(cos(turtle->rAngle) * -turtle->distance);
    int dCol = round(sin(turtle->rAngle) * turtle->distance); 
    //(if not postscript) -> store (start + delta)
    // turtle->colour = 'W';
    int newRow = prevRow + dRow;
    int newCol = prevCol + dCol;
    if(Bresenham(turtle, prevRow, prevCol, newRow, newCol, dRow, dCol)){
        //should store before in Func2
        turtle->row = newRow;
        turtle->col = newCol;
        return true;
    }
    return false;
}

//TODO: need to take what algorithm does, break into smaller testable functions
//TODO: Remove parameters?/need to break down into smaller functions
bool Bresenham(Program *turtle, int rowStart, int colStart, int rowEnd, int colEnd, int dRow, int dCol){
    int signRow = rowStart < rowEnd ? 1 : -1;
    int signCol = colStart < colEnd ? 1 : -1;
    //TODO: ask why putting this before (func call) produces runtime error
    dRow = abs(dRow);
    dCol = abs(dCol);
    if(!drawPoint(turtle, rowStart, colStart)){
        return false;
    }
    //TODO: Is rowStart-rowEnd not same as dRow/dCol?
    int error = dCol - dRow;
    while(abs(rowStart - rowEnd) > 1 || abs(colStart - colEnd) > 1){
        //TODO: This should be in updatePos function; given the error and dRow,dCol,colStart,rowStart
        int doubleError = DOUBLE * error;
        if(doubleError >= -dRow){
            error -= dRow;
            colStart += signCol;
        }
        if(doubleError <= dCol){
            error += dCol;
            rowStart += signRow;
        }
        if(!drawPoint(turtle, rowStart, colStart)){
            return false;
        }
    }
    return true;
}

bool isWithinBounds(int row, int col){
    return row >= 0 && row < ROW && col >= 0 && col < COL;
}

void test_isWithinBounds(){
    assert(isWithinBounds(0, 0) == true);
    assert(isWithinBounds(ROW, COL) == false);
    assert(isWithinBounds(SROW, SCOL) == true);
    assert(isWithinBounds(ROW-1, COL-1) == true);
    assert(isWithinBounds(ROW + 1, COL + 1) == false);
    assert(isWithinBounds(-1, 0) == false);
    assert(isWithinBounds(0, -1) == false);
    assert(isWithinBounds(ROW, 0) == false);
    assert(isWithinBounds(0, COL) == false);
}

bool drawPoint(Program *turtle, int row, int col){
    if(isWithinBounds(row, col)){
        turtle->SCREEN[row][col] = turtle->colour;
        return true;
    }
    return false;
}


//TODO: Gets hard to test - testing for edge case very difficult! Log.
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
        if(Num(turtle)){
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
    char *colVal = subStr(turtle->wds[turtle->cw]);
    setCol(turtle, colVal);
    return true;
}

//TODO: Define as helper function in .h file
char* subStr(char *str){
    if (str == NULL) {
        return NULL;
    }
    int len = strlen(str);
    for (int i = 1; i < len - 1; i++){
        str[i - 1] = str[i];
    }
    str[len - DOUBLE] = '\0';
    return str;
}
//Fully tested!
void test_subStr(void){
    char black[] = "\"BLACK\"";
    assert(STRSAME(subStr(black), "BLACK"));
    char red[] = "\"RED\"";
    assert(STRSAME(subStr(red), "RED"));
    char green[] = "\"GREEN\"";
    assert(STRSAME(subStr(green), "GREEN"));
    char blue[] = "\"BLUE\"";
    assert(STRSAME(subStr(blue), "BLUE"));
    char yellow[] = "\"YELLOW\"";
    assert(STRSAME(subStr(yellow), "YELLOW"));
    char cyan[] = "\"CYAN\"";
    assert(STRSAME(subStr(cyan), "CYAN"));
    char magenta[] = "\"MAGENTA\"";
    assert(STRSAME(subStr(magenta), "MAGENTA"));
    char white[] = "\"WHITE\"";
    assert(STRSAME(subStr(white), "WHITE"));
}

//TODO: Should I use lookup table to condense function?
void setCol(Program *turtle, char* colour){
    if (STRSAME(colour, "BLACK")){
        turtle->colour = 'B';
        neillfgcol(black);
    } 
    else if (STRSAME(colour, "WHITE")){
        turtle->colour = 'W';
        neillfgcol(white);
    } 
    else if (STRSAME(colour, "RED")){
        turtle->colour = 'R';
        neillfgcol(red);
    } 
    else if (STRSAME(colour, "GREEN")){
        turtle->colour = 'G';
        neillfgcol(green);
    } 
    else if (STRSAME(colour, "BLUE")){
        turtle->colour = 'B';
        neillfgcol(blue);
    } 
    else if (STRSAME(colour, "YELLOW")){
        turtle->colour = 'Y';
        neillfgcol(yellow);
    } 
    else if (STRSAME(colour, "CYAN")){
        turtle->colour = 'C';
        neillfgcol(cyan);
    } 
    else if (STRSAME(colour, "MAGENTA")){
        turtle->colour = 'M';
        neillfgcol(magenta);
    } 
    else {
        turtle->colour = 'W';
        neillfgcol(white);
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
    result = degToRad(FULLCIRC);
    assert(result >= 6.1 && result <= 6.3);
    // Test conversion of -360 degrees
    result = degToRad(-FULLCIRC);
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
