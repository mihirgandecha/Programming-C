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
    // free(turtle->s);
    free(turtle);
    test();
    RESULTS();
    return lfails != 0;
    // return 0;
} 

void test(void){
    puts("\n");
    // RUN("[INTERP] Set Function Test", test_interpSetNum_edge_cases);
    // RUN("[INTERP] Bresenham Algorithm Test", testBresenham);
    RUN("[HELPER] Substring Test", test_subStr);
    RUN("[HELPER] Screen Bound Test", test_isWithinBounds);
    RUN("[HELPER] Comparing float Test", test_compareFloat);
    RUN("[HELPER] Degree to Radians Test", degToRadTest);
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
    turtle->varTemp = turtle->wds[turtle->cw];
    int index = INDEX(*turtle->varTemp);
    if(turtle->store[index].inUse == true){
        ERROR("Variable already used!");
    } 
    turtle->cw++;
    if (!STRSAME(turtle->wds[turtle->cw], "OVER")){
        return false;
    }
    turtle->cw++;
    int startList = turtle->cw;
    if (!Lst(turtle)){
        return false;
    }
    
    int cList = turtle->cw;
    // int listLen = turtle->cw - cList;
    storeList(turtle, startList, cList);
    stack_free(turtle->s);
    return true;
}

// bool storeList(Program *turtle, int startList, int cList, int listLen){
//     int index = INDEX(*turtle->varTemp);
//     if(turtle->store[index].inUse == true){
//         ERROR("Variable already in use!");
//         return false;
//     }
//     for(int i = startList; i < cList; i++){
//         if(STRSAME(turtle->wds[startList], "{") || STRSAME(turtle->wds[startList], "{")){
//             startList++;
//             storeList(turtle, startList, cList, listLen);
//         }
//         strcpy(turtle->store[index].var, turtle->wds[startList]);
//         turtle->store[index].inUse = true;
//         if(Inslst(turtle) == false){
//             return false;
//         }
//         memset(turtle->store[index].var, 0, sizeof(turtle->store[index].var));
//         turtle->store[index].inUse = false;
//         if(startList != cList){
//             startList++;
//             storeList(turtle, startList, cList, listLen);
//         }
//         return true;
//     }
//     return false;
// }
// bool storeList(Program *turtle, int startList, int cList){
//     int index = INDEX(*turtle->varTemp);
//     for(int i = startList; i < cList; i++){
//         turtle->cw = i;
//         if(STRSAME(turtle->wds[i], "{") || STRSAME(turtle->wds[i], "\' '")){
//             storeList(turtle, startList, cList);
//         }
//         strcpy(turtle->store[index].var, turtle->wds[i]);
//         turtle->store[index].inUse = true;
//         if (Word(turtle) || Varnum(turtle)){
//             turtle->cw = cList;
//             if(!Inslst(turtle)){
//                 turtle->store[index].inUse = false;
//                 return false;
//             }
//         }
//         turtle->store[index].inUse = false;
//     }
//     return true;
// }

bool storeList(Program *turtle, int startList, int cList){
    int index = INDEX(*turtle->varTemp);
    for(int i = cList - 1; i >= startList; i--){
        turtle->cw = i;
        if(!STRSAME(turtle->wds[i], "{") && !STRSAME(turtle->wds[i], "}")){
            strcpy(turtle->store[index].var, turtle->wds[i]);
            turtle->store[index].inUse = true;
            if (Word(turtle) || Varnum(turtle)){
                turtle->cw = cList;
                if(!Inslst(turtle)){
                    turtle->store[index].inUse = false;
                    return false;
                }
            }
        turtle->store[index].inUse = false;
        }
    }
    return true;
}


// bool setList(Program *turtle){
//     //find start and end of loop
//     stacktype start = "{";
//     stacktype c;
//     stack_peek(turtle->s, &c);
//     if(!(STRSAME(c, start))){
//         return false;
//     }
//     //find its pair
//     int endP;
//     endP = findEnd(turtle);     
//     //Making sure stack is in right place:
//     if(turtle->s->size > 0){
//         if(!(STRSAME(turtle->s->start->i, "{") && STRSAME(turtle->s->end->i, "}"))){
//             return false;
//         }
//     }
//     if(!(processLoop(turtle, endP))){
//         return false;
//     }
//     return true;
// }

// bool processLoop(Program *turtle, int endP){
//     for(int i = 0; i <= endP; i++){
//         int index = INDEX(*turtle->varTemp);
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         strcpy(turtle->store[index].var, d);
//         if (turtle->s->size > 0 && (Word(turtle) || Varnum(turtle))){
//             if(Inslst(turtle)){
//                 queue_pop(turtle->s, &d);
//                 turtle->store[index].inUse = false;
//             }
//             if(turtle->s->size == 0){
//                 return true;
//             }
//         }
//         return setList(turtle);
//     }
//     return false;
// }

// int findEnd(Program *turtle){
//     int startP = 0;
//     //find its pair
//     int endP;
//     while (startP <= turtle->s->size){
//         stacktype end = "}";
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         if STRSAME(d, end){
//             endP = startP;
//             return endP;
//         }
//         startP++;
//     }
//     return 1;
// }

//     for(int i = startList; i < cList; i++){
//         turtle->cw = startList;
//         if(STRSAME(turtle->wds[startList], "{") || STRSAME(turtle->wds[startList], "\' '")){
//             startList++;
//             storeList(turtle, startList, cList);
//         }
//         stacktype d;
//         stack_peek(turtle->s, &d);
//         strcpy(turtle->store[index].var, d);
//         turtle->store[index].inUse = true;
//         if (turtle->s->size > 0 && (Word(turtle) || Varnum(turtle))){
//             turtle->cw = cList;
//             Inslst(turtle);
//             queue_pop(turtle->s, &d);
//             turtle->store[index].inUse = false;
//             startList++;
//         }
//     }
//     return;
// }

bool Set(Program *turtle){
    if(!STRSAME(turtle->wds[turtle->cw], "SET")){
        DEBUG("Expected 'SET'");
        return false;
    }
    turtle->cw++;
    if(!Ltr(turtle)){
        return false;
    }
    turtle->varTemp = &turtle->wds[turtle->cw][0];
    int index = INDEX(*turtle->varTemp);
    turtle->store[index].inUse = true;
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
        // turtle->numUsed = true;
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
        // turtle->varUsed = true;
        // store(turtle);
        
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
        stack_push(turtle->s, turtle->wds[turtle->cw]);        
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
        int index = INDEX(*turtle->varTemp);
        if(turtle->store[index].inUse == true){
            strcpy(turtle->store[index].var, turtle->wds[turtle->cw]);
        }    
        turtle->cw++;
        return Pfix(turtle);
    }
    return false;
}

// void intPfxix(Program *turtle){
//    char input[MAXCMND];
//    stacktype d, g1, g2;

//    stack* s = stack_init();
//    while(fgets(input, MAXCMND, stdin)){
//       /* If number push */
//       if(sscanf(input, FORMATSTR, &d)==1){
//          stack_push(s, d);
//       }
//       else{
//          /* Must be an operator ? */
//          assert(stack_pop(s, &g2));
//          assert(stack_pop(s, &g1));
//          switch(input[0]){
//             case '+' :
//                d = g1 + g2;
//                break;
//             case '-' :
//                d = g1 - g2;
//                break;
//             case '*' :
//                d = g1 * g2;
//                break;
//             case '/' :
//                d = g1 / g2;
//                break;
//             default:
//                fprintf(stderr, "Can't understand that ? %i\n", input[0]);
//                exit(EXIT_FAILURE);
//          }
//          stack_push(s, d);
//       }
//    }
//    assert(stack_pop(s, &d));
//    printf("Answer = ");
//    printf(FORMATSTR, d);
//    printf("\n");
   
//    if(stack_peek(s, &d) == true){
//       fprintf(stderr, "Stack still had items on it ?\n");
//       exit(EXIT_FAILURE);
//    }
//    stack_free(s);
//    return 0;
// }


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
