#include "interp.h"
#include "../neillsimplescreen.h"
#include "mintest.h"
#include "Stack/specific.h"


int main(int argc, char* argv[]){
    validArgs(argc);
    FILE* fttl = openFile(argv[1]);
    Program* turtle = initTurtle();
    initScrn(turtle);
    readWords(fttl, turtle);
    runProgram(turtle);
    if(argc > DOUBLE){
        writeFile(argv[DOUBLE], turtle);
    }
    /*TODO:
    1. move printtoscreen after FWD interp after new pos updated
    2. Flag in main if SCREEN or if TXT and store in turtle
    3. After pos updated in FWD, if -Flag- printscreen or other
    */
    else{
        printtoscreen(turtle);
    }
    fclose(fttl);
    if (turtle->simpleSet != NULL){
        freeStoreNum(turtle);
    }
    if (turtle->store != NULL){
        freeStorage(turtle);
    }
    if(turtle->s != NULL){
        stack_free(turtle->s);
    }
    free(turtle);
    // test();
    return 0;
} 

// static size_t test(void){
//     puts("\n");
//     // RUN("[INTERP] Set Function Test", test_interpSetNum_edge_cases);
//     // RUN("[INTERP] Bresenham Algorithm Test", testBresenham);
//     RUN("[HELPER] Substring Test", test_subStr);
//     RUN("[HELPER] Screen Bound Test", test_isWithinBounds);
//     RUN("[HELPER] Comparing float Test", test_compareFloat);
//     RUN("[HELPER] Degree to Radians Test", degToRadTest);
//     RESULTS();
//     return lfails != 0;
// }

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
void writeFile(char* filename, Program *turtle){
    //concasinate to buffer without causing to reset
    //Another functio
    char filepath[BUFFER] = {"\0"};
    snprintf(filepath, sizeof(filepath), "myResults/%s", filename);
    printf("%s", filepath);
    FILE* fttx = fopen(filepath, "w");
    if(!fttx){
        ERROR("Cannot read from argv[2] \n");
        // fclose(fttx);
        // exit(EXIT_FAILURE);
    }
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            fprintf(fttx, "%c", turtle->SCREEN[row][col]);
        }
        fprintf(fttx, "\n");
    }
    fclose(fttx);
    // return fttx;
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

void initInstruct(Program *turtle){
    turtle->store[turtle->loopIndx] = (Variable*)calloc(1, sizeof(Variable));
    if (!turtle->store[turtle->loopIndx]){
        ERROR("simpleSet failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    int tempCw;
    for (tempCw = 0; tempCw < MAXTOKENSIZE; tempCw++){
        turtle->store[turtle->loopIndx]->var[tempCw][MAXTOKENSIZE] = NULL;
    }
    turtle->store[turtle->loopIndx]->cInst = 0;
}

//TODO: Test + should I put into initTurtle?
void initPos(Program *turtle){
    turtle->col = SCOL;
    turtle->row = SROW;
    turtle->rAngle = 0;
    turtle->colour = 'W';
    for(int i = 0; i < MAX_VARS; i++){
        turtle->setUsed[i] = false;
    }
    initStack(turtle);
    turtle->s->start = NULL;
}

//TODO: Test how?
void readWords(FILE* fttl, Program* turtle){
    if(!checkNull(turtle)){
        return;
    }
    int i = 0;            
    turtle->varTemp = NULL;
    while((fscanf(fttl, "%s", turtle->wds[i])) == 1){
        i++;
    }
}
//TODO: Test how?
void runProgram(Program* turtle){
    // turtle->numUsed = false;
    // turtle->varUsed = false;
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
        //TODO Seconds need to be 1 seconds
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
        varFwd(turtle);
    }
    return true;
}

void varFwd(Program *turtle){
    if(Num(turtle)){
        turtle->distance = atof(turtle->wds[turtle->cw]);
        intFwd(turtle);
    }
    if(Var(turtle)){
        int index = INDEX(turtle->wds[turtle->cw][1]);
        if(turtle->setUsed[index] == true){
            int cw = turtle->store[turtle->loopIndx]->cInst;
            turtle->distance = atof(turtle->store[index]->var[cw]);
            intFwd(turtle);
        }
    }
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
    CHAR_EQUAL(testTurtle->SCREEN[SROW][SCOL], 'W');
    CHAR_EQUAL(testTurtle->SCREEN[SROW - 1][SCOL], 'W');
    CHAR_EQUAL(testTurtle->SCREEN[SROW - 2][SCOL], 'W');
    CHAR_EQUAL(testTurtle->SCREEN[SROW - 3][SCOL], 'W');
    CHAR_EQUAL(testTurtle->SCREEN[SROW - 4][SCOL], 'W');
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
        varAngle(turtle);
    }
    return true;
}

void varAngle(Program *turtle){
    if(Num(turtle)){
            double angle = atof(turtle->wds[turtle->cw]);
            turtle->rAngle = turtle->rAngle + degToRad(angle);
        }
    if(Var(turtle)){
        int index = INDEX(turtle->wds[turtle->cw][1]);
        if(turtle->setUsed[index] == true){
            int cw = turtle->store[index]->cInst;
            double angle = atof(turtle->store[index]->var[cw]);
            turtle->store[index]->cInst++;
            turtle->rAngle = turtle->rAngle + degToRad(angle);
        }
    }
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
//TODO Remove after Fully tested!
void test_subStr(void){
    char black[] = "\"BLACK\"";
    STR_EQUAL(subStr(black), "BLACK");
    char red[] = "\"RED\"";
    STR_EQUAL(subStr(red), "RED");
    char green[] = "\"GREEN\"";
    STR_EQUAL(subStr(green), "GREEN");
    char blue[] = "\"BLUE\"";
    STR_EQUAL(subStr(blue), "BLUE");
    char yellow[] = "\"YELLOW\"";
    STR_EQUAL(subStr(yellow), "YELLOW");
    char cyan[] = "\"CYAN\"";
    STR_EQUAL(subStr(cyan), "CYAN");
    char magenta[] = "\"MAGENTA\"";
    STR_EQUAL(subStr(magenta), "MAGENTA");
    char white[] = "\"WHITE\"";
    STR_EQUAL(subStr(white), "WHITE");
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
    turtle->loopIndx = INDEX(turtle->wds[turtle->cw][0]);
    assert(turtle->s->start == NULL);
    stacktype d = &turtle->wds[turtle->cw][0];
    stack_push(turtle->s, d);  

    turtle->cw++;
    if (!STRSAME(turtle->wds[turtle->cw], "OVER")){
        return false;
    }
    turtle->cw++;
    turtle->loopItems[turtle->loopIndx] = 0;
    if (!Lst(turtle)){
        return false;
    }
    // while(turtle->s->size > 0){
    //     // stack_peek(turtle->s, &turtle->d);
    //     int index = turtle->loopIndx;
    //     int cwMax = turtle->store[index]->cInst;
    //     for(int tempCw = 0; tempCw <= cwMax; tempCw++){
    //         stack_pop(turtle->s, &d);
    //         printf("%s", d);
    //         stack_push(turtle->s, turtle->store[index]->var);

    //         if (!Inslst(turtle)){
    //             return false;
    //         }
    //     }
    // return true;
    // }
    if (!Inslst(turtle)){
                return false;
            }
    return true;
}

//want to pop B
    //set B->list_item[start->end]
// pStack(Program *turtle){
//     while(turtle->s->size > 0){
//         // stack_peek(turtle->s, &turtle->d);
//         stack_pop(turtle->s, &turtle->d);
//         int index = turtle->loopIndx;
//         int cwMax = turtle->store[index]->cInst;
//         for(int tempCw = 0; tempCw <= cwMax; tempCw++){
//             strncpy(turtle->d, turtle->store[turtle->loopIndx]->var[tempCw], MAXTOKENSIZE);
//             memmove(&turtle->wds[turtle->cw + 1], &turtle->wds[turtle->cw], (MAXCMND - turtle->cw - 1) * sizeof(turtle->wds[0]));
//             //Fix SET instruction!
//             snprintf(turtle->wds[turtle->cw], MAXTOKENSIZE, "SET %s", turtle->d);
//             if (!Inslst(turtle)){
//                 return false;
//             }
//         }
//     return true;
//     }
// }

void initStack(Program *turtle){
    //Had memory leak when in this function
    assert(stack_free(NULL));
    //make sure it has nothing copied over
    assert(!stack_peek(NULL, &turtle->d));
    turtle->s = stack_init();
    int index = turtle->loopIndx;
    turtle->s[index].size = 0;
    turtle->s[index].start = NULL;
    
    // turtle->s->loopIndex = INDEX(turtle->wds[turtle->cw][0]);
    // turtle->s->loopCw = 0;
    // turtle->s->size = 1;
    // stack_tostring(turtle->s, turtle->str);
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
    //TODO should be array:
    // turtle->numUsed = false;
    // turtle->varUsed = false;
    // turtle->varTemp = turtle->wds[turtle->cw];
    turtle->loopIndx = INDEX(turtle->wds[turtle->cw][0]);
    turtle->setUsed[turtle->loopIndx] = true;
    //Remember that Ltr is turtle->wds[turtle->cw - 2]
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

bool store(Program* turtle){
    int index = turtle->loopIndx;
    if((turtle->setUsed[index]) == true){
        initInstruct(turtle);
    }
    int tempCw = turtle->store[index]->cInst;
    while(turtle->store[index]->var[tempCw] != NULL){
        tempCw++;
    }
    turtle->store[index]->cInst = tempCw;
    strcpy(turtle->store[index]->var[tempCw], turtle->wds[turtle->cw]);
    // if(turtle->numUsed == true){
    //     // int tempUseIndx = turtle->store[turtle->loopIndx]->inUseIndx;
    //     int cw = turtle->store[index]->cInst;
    //     strcpy(turtle->store[index]->var[cw], turtle->wds[turtle->cw]);
    //     turtle->store[index]->cInst++;
    //     turtle->store[index]->inUse = true;
    //     return true;
    // }
    // else if(turtle->varUsed == true){
    //     // int tempUseIndx = turtle->store[index]->inUseIndx;
    //     int cw = turtle->store[index]->cInst;
    //     strcpy(turtle->store[index]->var[cw], turtle->wds[turtle->cw]);
    //     turtle->store[index]->cInst++;
    //     turtle->store[index]->inUse = true;
    //     // turtle->store[index]->inUse[turtle->store[index]->inUseIndx]++;
    //     return true;
    // }
    return true;
}

bool findInstrStore(Program *turtle){
    int tempUseIndx = 0;
    while(turtle->store[turtle->loopIndx]->var != NULL){
        tempUseIndx++;
        if(tempUseIndx == MAXTOKENSIZE){
            return false;
        }
    }
    // turtle->store[turtle->loopIndx]->inUseIndx = tempUseIndx;
    turtle->setUsed[turtle->loopIndx] = true;
    return true;
}

bool Num(Program *turtle){
    char *number = turtle->wds[turtle->cw];
    char *endptr;
    strtod(number, &endptr);
    if (*endptr == '\0'){
        turtle->numUsed = true;
        // store(turtle);
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
        turtle->varUsed = true;
        store(turtle);
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
            turtle->varTemp = var;
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
        //pop Variable here
        return true;
    }
    else{
    while(Item(turtle)){
        int index = turtle->loopIndx;
        // turtle->s
        if(turtle->store[index] == NULL){
            turtle->store[index] = (Variable*)calloc(1, sizeof(Variable));
            turtle->store[index]->cInst = 0;
        }
        if(!pushInstr(turtle)){
            return false;
        }
        turtle->cw++;
        return Items(turtle);
    }
    }
    return false;
        
}

// //copy instr from <INSLST> in loop for each item
bool pushInstr(Program* turtle){
    int index = turtle->loopIndx;
    int cw = turtle->store[index]->cInst;
    strcpy(turtle->store[index]->var[cw], turtle->wds[turtle->cw]);
    turtle->store[index]->cInst++;
    turtle->store[index]->inUse = true;
    return true;
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
    //TODO: Interpreter should not store...but interprets
    if(STRSAME(turtle->wds[turtle->cw], ")")){
        return true;
    }
    else if (Op(turtle)){
        turtle->cw++;
        return Pfix(turtle);
    }
    else if (Varnum(turtle)){    
        store(turtle);
        turtle->cw++;
        return Pfix(turtle);
    }
    return false;
}

void interpSetNum(Program* turtle){
    // int index = *turtle->varTemp - 'A';
    int index = turtle->loopIndx;
    // printf("%s", turtle->wds[turtle->cw]);
    double numVal = atof(turtle->wds[turtle->cw]);
    turtle->simpleSet[index] = (storeNum*)calloc(1, sizeof(storeNum));
    if (!turtle->simpleSet){
        ERROR("simpleSet failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    turtle->simpleSet[index]->var = *turtle->varTemp;
    turtle->simpleSet[index]->value = numVal;
}

void test_interpSetNum_edge_cases(void){
    Program *testTurtle =  initTurtle();
    testTurtle->cw = 0;
    char varTemp;
    double tempVal = 5;
    int index;
    //First testing that value can be stored from A->Z
    for(varTemp = 'A'; varTemp <= 'Z'; varTemp++){
        testTurtle->wds[testTurtle->cw][0] = varTemp;
        testTurtle->varTemp = &varTemp;
        testTurtle->cw++;
        testTurtle->wds[testTurtle->cw][0] = tempVal;
        interpSetNum(testTurtle);
        index = varTemp - 'A';
        CHAR_EQUAL(testTurtle->simpleSet[index]->var, varTemp);
        testTurtle->cw = 0; // Reset the current word index for the next test
    }
    freeStoreNum(testTurtle);
    free(testTurtle);
}

int compareFloat(double a, double b){
    if (fabs(a - b) < THRESHHOLD){
        return 0;
    }
    return 1;
}

void test_compareFloat(){
    double a = 5.0;
    double b = 5.0;
    double c = 5.01;
    INT_EQUAL(compareFloat(a, b), 0);
    INT_EQUAL(compareFloat(a, c), 1);
}

bool freeStoreNum(Program* turtle){
    for(int index = 0; index < MAX_VARS; index++){
        if(turtle->simpleSet[index] != NULL){
            free(turtle->simpleSet[index]);
            turtle->simpleSet[index] = NULL;
        }
    }
    return true;
}

bool freeStorage(Program* turtle){
    for(int index = 0; index < MAX_VARS; index++){
        if(turtle->store[index] != NULL){
            free(turtle->store[index]);
            turtle->store[index] = NULL;
        }
    }
    return true;
}

void degToRadTest(void){
    double result;
    result = degToRad(0);
    INT_EQUAL((int)result, 0);
    result = degToRad(-0);
    INT_EQUAL((int)result, 0);
    // assert((int)result == 0);
    // Test conversion of 360 degrees
    result = degToRad(FULLCIRC);
    INTO_RANGE(result, 6.1, 6.3);
    // assert(result >= 6.1 && result <= 6.3);
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
