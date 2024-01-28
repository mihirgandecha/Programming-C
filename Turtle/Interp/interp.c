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
    turtle->isScreen = (argc != DOUBLE) ? false : true;
    runProgram(turtle);
    if(argc == MIN_ARGS){
        writeFile(argv[MIN_ARGS], turtle);
    }
    fclose(fttl);
    stack_free(turtle->s);
    // free(turtle->s);
    free(turtle);
    test();
    RESULTS();
    return lfails != 0;
    // return 0;
} 

void test(void){
    puts("\n");
    // RUN("[INTERP] Bresenham Algorithm Test", testBresenham);
    RUN("[HELPER] Substring Test", test_subStr);
    RUN("[HELPER] Screen Bound Test", test_isWithinBounds);
    RUN("[HELPER] Comparing float Test", test_compareFloat);
    RUN("[HELPER] Degree to Radians Test", degToRadTest);
    RUN("[HELPER] Set Test", testSet);
    RUN("[HELPER] PFix Test", test_pFixNum);
    RUN("[HELPER] PFix Test", test_pFixVar);
}

void validArgs(int argc){
    if(argc > MIN_ARGS){
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
        exit(EXIT_FAILURE);
    }
    return fttl;
}

void writeFile(char* filename, Program *turtle){
    char filepath[BUFFER] = {"\0"};
    snprintf(filepath, sizeof(filepath), "myResults/%s", filename);
    printf("%s", filepath);
    FILE* fttx = fopen(filepath, "w");
    if(!fttx){
        ERROR("Cannot read from argv[2] \n");
        fclose(fttx);
        exit(EXIT_FAILURE);
    }
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            fprintf(fttx, "%c", turtle->SCREEN[row][col]);
        }
        fprintf(fttx, "\n");
    }
    fclose(fttx);
}

// void pFixWrite(Program* turtle) {
//     if (turtle->pfixUsed == true){
//         FILE* psFile = fopen("output.ps", "w");
//         if (psFile == NULL) {
//             perror("Error opening file");
//             return;
//         }
//         fprintf(psFile, "%% Placeholder PostScript commands\n");
//         fclose(psFile);
//         system("ps2pdf output.ps output.pdf");
//     }
// }

Program* initTurtle(void){
    Program* turtle = (Program*)calloc(1, sizeof(Program));
    if (!turtle){
        ERROR("Turtle failed to initialise!\n");
        exit(EXIT_FAILURE);
    }
    turtle->col = SCOL;
    turtle->row = SROW;
    turtle->rAngle = 0;
    turtle->colour = ' ';
    turtle->isScreen = false;
    turtle->s = stack_init();
    turtle->s->start = NULL;
    turtle->colour = 'W';
    return turtle;
}

void initScrn(Program *turtle){
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            turtle->SCREEN[row][col] = ' ';
        }
    }
}

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

void runProgram(Program* turtle){
    if(!Prog(turtle)){
        ERROR("Grammar mistakes found in ttl.");
        exit(EXIT_FAILURE);
    }
}


//TODO: Format: remove puts?
//TODO: Format: how many seconds delay and in right placement?
void printtoscreen(Program *turtle){
    neillclrscrn();
    neillcursorhome();
    double seconds = 0.25;
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            printf("%c", turtle->SCREEN[row][col]);
        }
        printf("\n");
    }
    neillbusywait(seconds);
    neillreset();
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
    if(STRSAME(turtle->wds[turtle->cw], "END")){
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
        double distance = atof(turtle->wds[turtle->cw]);
        intFwd(turtle, distance);
    }
    if(Var(turtle)){
        int index = INDEX(turtle->wds[turtle->cw][1]);
        if(turtle->store[index].inUse == true){
            double distance = atof(turtle->store[index].var);
            intFwd(turtle, distance);
        }
    }
}

bool intFwd(Program *turtle, double distance){
    if(fabs(distance) > COL){
        return false;
    }
    int prevCol = (int)turtle->col;
    int prevRow = (int)turtle->row; 
    int dRow = round(cos(turtle->rAngle) * -distance);
    int dCol = round(sin(turtle->rAngle) * distance); 
    //(if not postscript) -> store (start + delta)
    int newRow = prevRow + dRow;
    int newCol = prevCol + dCol;
    if(Bresenham(turtle, newRow, newCol, dRow, dCol)){
        return true;
    }
    return false;
}

bool Bresenham(Program *turtle, int rowEnd, int colEnd, int dRow, int dCol){
    int signRow = turtle->row < rowEnd ? 1 : -1;
    int signCol = turtle->col < colEnd ? 1 : -1;
    dRow = abs(dRow);
    dCol = abs(dCol);
    int error = dCol - dRow;
    while((turtle->row != rowEnd) || (turtle->col != colEnd)){
        if(!drawPoint(turtle, turtle->row, turtle->col)){
            return false;
        }
        updatePoints(turtle, error, dRow, dCol, signRow, signCol);
    }
    if(turtle->SCREEN[rowEnd][colEnd] == ' '){
        drawPoint(turtle, rowEnd, colEnd);
    }
    if (turtle->colour != 'W'){
        setCol(turtle, turtle->setColour);
    }
    if(turtle->isScreen == true){
        printtoscreen(turtle);
    }
    return true;
}

void updatePoints(Program *turtle, int error, int dRow, int dCol, int signRow, int signCol){
    int doubleError = DOUBLE * error;
    if(doubleError >= -dRow){
        error -= dRow;
        turtle->col += signCol;
    }
    if(doubleError <= dCol){
        error += dCol;
        turtle->row += signRow;
    }
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

void test_Bresenham(){
    Program turtle;
    // TODO init test input values into turtle
    assert(Bresenham(&turtle, 10, 10, 5, 5) == false);
    // testing for updating position
    turtle.row = 0;
    turtle.col = 0;
    Bresenham(&turtle, 10, 10, 5, 5);
    assert(turtle.row == 5 && turtle.col == 5);
    //testing negative dRow and dCol
    turtle.row = 10;
    turtle.col = 10;
    Bresenham(&turtle, 0, 0, -5, -5);
    assert(turtle.row == 5 && turtle.col == 5);
    //row handling test
    turtle.row = 10;
    turtle.col = 0;
    Bresenham(&turtle, 0, 10, -5, 5);
    assert(turtle.row == 5 && turtle.col == 5);
    // col handling test
    turtle.row = 0;
    turtle.col = 10;
    Bresenham(&turtle, 10, 0, 5, -5);
    assert(turtle.row == 5 && turtle.col == 5);
}


void testBresenham(void){
    Program *testTurtle = initTurtle();
    testTurtle->col = SCOL;
    testTurtle->row = SROW;
    testTurtle->rAngle = 0;
    initScrn(testTurtle);
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
        if(turtle->store[index].inUse == true){
            double angle = atof(turtle->store[index].var);
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
    //TODO make work with set
    if(!Var(turtle) && !Word(turtle)){
        return false;
    }
    char *colVal = subStr(turtle->wds[turtle->cw]);
    turtle->setColour = colVal;
    setCol(turtle, colVal);
    return true;
}

void varCol(Program *turtle){
    if(Var(turtle)){
        int index = INDEX(turtle->wds[turtle->cw][1]);
        if(turtle->store[index].inUse == true){
            char *colVal = subStr(turtle->store[index].var);
            turtle->setColour = colVal;
            setCol(turtle, colVal);
        }
    }
    else if(Word(turtle)){
        char *colVal = subStr(turtle->wds[turtle->cw]);
        turtle->setColour = colVal;
        setCol(turtle, colVal);
    }
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


//@Lws

bool Loop(Program *turtle){
    if (!STRSAME(turtle->wds[turtle->cw], "LOOP")){
        return false;
    }
    turtle->cw++;
    if (!Ltr(turtle)){
        return false;
    }
    turtle->varTemp = turtle->wds[turtle->cw];
    int index = INDEX(*turtle->varTemp);
    turtle->cw++;
    if (!STRSAME(turtle->wds[turtle->cw], "OVER")){
        return false;
    }
    int startList = turtle->cw;
    //startList = cw
    //if ! Lst() return false
    //int loopLen = cw - startList
    //startLooping(turtle, letter, loop_len)
    turtle->cw++;
    if (!Lst(turtle)){
        return false;
    }
    char str[1000];
    stack_tostring(turtle->s, str);
    printf("%s", str);
    int loop_len = turtle->cw - startList;
    startLooping(turtle, index, loop_len);
    // int listLen = turtle->cw - cList;
    // storeList(turtle, startList, cList);
    return true;
}

bool startLooping(Program *turtle, int letter, int loop_len){
    int startIndx = turtle->cw;
    for (int i = 0; i < loop_len; i++){
        turtle->cw = startIndx;
        stacktype d;
        if(!stack_pop(turtle->s, &d)){
            return false;
        }
        strcpy(turtle->store[letter].var, d);
        turtle->store[letter].inUse = true;
        if(!(Inslst(turtle))){
            return false;
        }
    }
    return true;
}


//startLooping(turtle, letter, loop_len)
//  int start_indx = turtle->cw
//  for(int i = 0; i<loopLen; i++)
//      turtle->cw = start_index
//      variables[letter] = stack pop
//      if ! Inslst return false



bool Set(Program *turtle){
    if(!STRSAME(turtle->wds[turtle->cw], "SET")){
        DEBUG("Expected 'SET'");
        return false;
    }
    turtle->cw++;
    if(!Ltr(turtle)){
        return false;
    }
    int index = INDEX(*turtle->varTemp);
    turtle->store[index].inUse = true;
    turtle->cw++;
    if(!STRSAME(turtle->wds[turtle->cw], "(")){
        DEBUG("Expected 'Opening '('");
        return false;
    }
    turtle->cw++;
    if(!Pfix(turtle, index)){
        return false;
    }
    return true; 
}

void testSet(void){
    Program* testTurtle = initTurtle();
    int index;
    // Test for SET A (5)
    strcpy(testTurtle->wds[0], "START");
    strcpy(testTurtle->wds[1], "SET");
    strcpy(testTurtle->wds[2], "A");
    strcpy(testTurtle->wds[3], "(");
    strcpy(testTurtle->wds[4], "5");
    strcpy(testTurtle->wds[5], ")");
    strcpy(testTurtle->wds[6], "END");
    testTurtle->cw = 1;
    Set(testTurtle);
    index = INDEX('A');
    BOOL(testTurtle->store[index].inUse == true);
    STR_EQUAL(testTurtle->store[index].var, "5");
    //Test for SET B ($C)
    strcpy(testTurtle->wds[2], "B");
    strcpy(testTurtle->wds[4], "$C");
    testTurtle->cw = 1;
    Set(testTurtle);
    index = INDEX(*testTurtle->varTemp);
    BOOL(testTurtle->store[index].inUse == true);
    STR_EQUAL(testTurtle->store[index].var, "$C");
    //Test for SET C ($A 1 +)
    strcpy(testTurtle->wds[2], "C");
    strcpy(testTurtle->wds[4], "$A");
    strcpy(testTurtle->wds[5], "1");
    strcpy(testTurtle->wds[6], "+");
    strcpy(testTurtle->wds[7], ")");
    strcpy(testTurtle->wds[8], "END");
    testTurtle->cw = 1;
    Set(testTurtle);
    //using $A = 5
    index = INDEX(*testTurtle->varTemp);
    double result = 6;
    double out_result = atof(testTurtle->store[index].var);
    FLOAT_EQUAL(result, out_result);
    //Test for SET D ($A $C *)
    strcpy(testTurtle->wds[2], "D");
    strcpy(testTurtle->wds[4], "$A");
    strcpy(testTurtle->wds[5], "$C");
    strcpy(testTurtle->wds[6], "*");
    strcpy(testTurtle->wds[7], ")");
    strcpy(testTurtle->wds[8], "END");
    testTurtle->cw = 1;
    Set(testTurtle);
    index = INDEX(*testTurtle->varTemp);
    BOOL(testTurtle->store[index].pfixUse == true);
    //using $A = 5 and $C = 6
    index = INDEX(*testTurtle->varTemp);
    double result2 = 30;
    double out_result2 = atof(testTurtle->store[index].var);
    FLOAT_EQUAL(result2, out_result2);
    // Test for SET $A ("RED")
    strcpy(testTurtle->wds[0], "START");
    strcpy(testTurtle->wds[1], "SET");
    strcpy(testTurtle->wds[2], "A");
    strcpy(testTurtle->wds[3], "(");
    strcpy(testTurtle->wds[4], "\"RED\"");
    strcpy(testTurtle->wds[5], ")");
    strcpy(testTurtle->wds[6], "END");
    testTurtle->cw = 1;
    Set(testTurtle);
    index = INDEX('A');
    BOOL(testTurtle->store[index].inUse == true);
    char* colour_out = subStr(testTurtle->store[index].var);
    STR_EQUAL(colour_out, "RED");
    stack_free(testTurtle->s);
    free(testTurtle);
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
        return true;
    }
    else{
        int temp = turtle->cw;
        turtle->cw++;
        if(!(Items(turtle))){
            return false;
        }
        while(!(STRSAME(turtle->wds[temp], "{"))){
            stack_push(turtle->s, turtle->wds[temp--]); 
            return true;       
        }
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


bool Pfix(Program* turtle, int index){
    if(!checkNull(turtle)){
        return false;
    }
    if(STRSAME(turtle->wds[turtle->cw], ")")){
        return true;
    }
    else if (Op(turtle)){
        int tempCw = turtle->cw;
        if(!(storeOP(turtle, index))){
            return false;
        }
        intOp(turtle, index);
        turtle->cw = tempCw;
        turtle->cw++;
        return Pfix(turtle,index);
    }
    else if (Varnum(turtle)){
        strcpy(turtle->store[index].var, turtle->wds[turtle->cw]);
        turtle->cw++;
        return Pfix(turtle, index);
    }
    else if (Word(turtle)){
        strcpy(turtle->store[index].var, turtle->wds[turtle->cw]);
        turtle->cw++;
        return Pfix(turtle, index);
    }
    return false;
}

bool storeOP(Program* turtle, int index){
    if(Op(turtle)){
        turtle->store[index].pfixUse = true;
        stack_push(turtle->s, turtle->wds[turtle->cw]);
        turtle->cw--;
        return storeOP(turtle, index);
    }
    if(Varnum(turtle)){
        if(turtle->store[index].pfixUse == true){
            stack_push(turtle->s, turtle->wds[turtle->cw]);
            turtle->cw--;
            return storeOP(turtle, index);
        }
    }
    if(STRSAME(turtle->wds[turtle->cw], "(")){
        return true;
    }
    return storeOP(turtle, index);
}

void intOp(Program* turtle, int index){
    stacktype op;
    stacktype bottom;
    stacktype top;
    stack_pop(turtle->s, &top);
    stack_pop(turtle->s, &bottom);
    stack_pop(turtle->s, &op);
    char Op = op[0];
    double topValue = pFixNum(top);
    if(DOUBLE_EQUAL(topValue, 1)){
        topValue = pFixVar(top, turtle);
    }
    double bottomValue = pFixNum(bottom);
    if(DOUBLE_EQUAL(bottomValue, 1)){
        bottomValue = pFixVar(bottom, turtle);
    }
    double result;
    switch(Op){
        case '+':
            result = bottomValue + topValue;
            break;
        case '-':
            result = bottomValue - topValue;
            break;
        case '*':
            result = bottomValue * topValue;
            break;
        case '/':
            if(!(compareFloat(topValue, 0)) && !(compareFloat(bottomValue, 0))){
                result = bottomValue / topValue;
            } else {
                ERROR("Error: Division by zero.\n");
            }
            break;
        default:
            ERROR("Error: Invalid operator.\n");
    }
    char str[MAXTOKENSIZE];
    DOUBLE_TO_STRING(str, result);
    sprintf(str, "%f", result);
    strcpy(turtle->store[index].var, str);
}

double pFixNum(stacktype d){
    char *number = d;
    char *endptr;
    double value = strtod(number, &endptr);
    if (*endptr == '\0'){
        return value;
    }
    else{
        return 1;
    }
}

void test_pFixNum(void){
    stacktype validNum = "123.45";
    stacktype invalidNum = "123abc";
    FLOAT_EQUAL(pFixNum(validNum), 123.45);
    //return 1 indicating not worked:
    FLOAT_EQUAL(pFixNum(invalidNum), 1);
}

double pFixVar(stacktype d, Program *turtle){
    char* varName = d;
    if (strlen(varName) != EXPECTED_VARLEN) {
        return 1;
    }
    if (varName[0] == '$' && isalpha(varName[1])){
        int index = INDEX(varName[1]);
        if(turtle->store[index].inUse == true){
            return atof(turtle->store[index].var);
        }
    }
    return 1; 
}

void test_pFixVar(void){
    Program* testTurtle = initTurtle();
    stacktype validNum = "123.45";
    stacktype invalidNum = "123abc";
    stacktype validVar = "$C";
    stacktype invalidVar = "$1";
    stacktype nonExistentVar = "$Z";
    testTurtle->store[INDEX('C')].inUse = true;
    strcpy(testTurtle->store[INDEX('C')].var, "123.45");
    FLOAT_EQUAL(pFixNum(validNum), 123.45);
    FLOAT_EQUAL(pFixNum(invalidNum), 1);
    FLOAT_EQUAL(pFixVar(validVar, testTurtle), 123.45);
    FLOAT_EQUAL(pFixVar(invalidVar, testTurtle), 1);
    FLOAT_EQUAL(pFixVar(nonExistentVar, testTurtle), 1);
    stack_free(testTurtle->s);
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

void degToRadTest(void){
    double result;
    result = degToRad(0);
    INT_EQUAL((int)result, 0);
    result = degToRad(-0);
    INT_EQUAL((int)result, 0);
    result = degToRad(FULLCIRC);
    INTO_RANGE(result, 6.1, 6.3);
    result = degToRad(-FULLCIRC);
    assert(result >= 6.1 && result <= 6.3);
    result = degToRad(90);
    assert(result >= 1.3 && result <= 1.6);
    result = degToRad(-90);
    assert(result >= 1.3 && result <= 1.6);
    result = degToRad(HALFCIRC);
    assert(result >= 3.10 && result <= 3.20);
    result = degToRad(-HALFCIRC);
    assert(result >= 3.10 && result <= 3.20);
    result = degToRad(270);
    assert(result >= 4.70 && result <= 4.80);
    result = degToRad(-270);
    assert(result >= 4.70 && result <= 4.80);
}
