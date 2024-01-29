#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../Parse/parse.h"

void test(void){
    Program* testTurtle = initTurtle();

    //Testing for End with runProgram:
    strcpy(testTurtle->wds[0], "START");
    strcpy(testTurtle->wds[1], "END");
    testTurtle->cw = 0;
    runProgram(testTurtle);

    //Testing that return false if no End
    strcpy(testTurtle->wds[1], "RIGHT");
    strcpy(testTurtle->wds[2], "45");
    strcpy(testTurtle->wds[3], "FORWARD");
    strcpy(testTurtle->wds[4], "20");
    testTurtle->cw = 0;

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
    assert(Num(testTurtle) == true);

    // Testing Num error msg ~ working
    strcpy(testTurtle->wds[0], "abc");
    testTurtle->cw = 0;
    assert(Num(testTurtle) == false);
    
    //Testing for Ltr Function:
    Program* testLtr = initTurtle();
    testLtr->cw = 0;
    strcpy(testLtr->wds[testLtr->cw], "A");
    assert(Ltr(testLtr) == true);
    strcpy(testLtr->wds[testLtr->cw], "M");
    assert(Ltr(testLtr) == true);
    strcpy(testTurtle->wds[testTurtle->cw], "c");
    assert(Ltr(testTurtle) == false);
    strcpy(testTurtle->wds[testTurtle->cw], "2");
    assert(Ltr(testTurtle) == false);
    strcpy(testTurtle->wds[testTurtle->cw], "@");
    assert(Ltr(testTurtle) == false);

    //Test for <VAR> Function:
    // Test 1: Valid variable
    strcpy(testTurtle->wds[0], "$A");
    testTurtle->cw = 0;
    assert(Var(testTurtle) == true);
    // Test 2: Invalid variable (length is not 2)
    strcpy(testTurtle->wds[0], "$AB");
    testTurtle->cw = 0;
    assert(Var(testTurtle) == false);
    // Test 3: Invalid variable (first character is not $)
    strcpy(testTurtle->wds[0], "A");
    testTurtle->cw = 0;
    assert(Var(testTurtle) == false);
    // Test 4: Invalid variable (second character is not an uppercase letter)
    strcpy(testTurtle->wds[0], "$a");
    testTurtle->cw = 0;
    assert(Var(testTurtle) == false);

    //Test for <VARNUM> Function
    // Test 1: Valid variable
    strcpy(testTurtle->wds[0], "$A");
    testTurtle->cw = 0;
    assert(Varnum(testTurtle) == true);
    // Test 2: Valid number
    strcpy(testTurtle->wds[0], "10");
    testTurtle->cw = 0;
    assert(Varnum(testTurtle) == true);
    // Test 3: Invalid input (not a variable or a number)
    Program* testTurtle2 = initTurtle();
    strcpy(testTurtle2->wds[0], "AB");
    testTurtle2->cw = 0;
    assert(Varnum(testTurtle2) == false);

    //Testing for <COL> function:
    strcpy(testTurtle2->wds[0], "COLOUR");
    strcpy(testTurtle2->wds[1], "$A");
    testTurtle2->cw = 0;
    assert(Col(testTurtle2) == true);

    // Test for <WORD> function:
    strcpy(testTurtle2->wds[0], "\"RED\"");
    testTurtle2->cw = 0;
    assert(Word(testTurtle2) == true);

    //Test <COL> with <WORD> function:
    strcpy(testTurtle2->wds[0], "COLOUR");
    strcpy(testTurtle2->wds[1], "\"RED\"");
    testTurtle2->cw = 0;
    assert(Col(testTurtle2) == true);

    //Test <ITEM> Function:
    strcpy(testTurtle->wds[0], "\"RED\"");
    testTurtle->cw = 0;
    assert(Item(testTurtle) == true);

    strcpy(testTurtle->wds[0], "ORANGE");
    testTurtle->cw = 0;
    assert(Item(testTurtle) == false);

    // Test for <ITEMS> function
    strcpy(testTurtle->wds[0], "}");
    testTurtle->cw = 0;
    assert(Items(testTurtle) == true);

    strcpy(testTurtle->wds[0], "$H");
    strcpy(testTurtle->wds[1], "}");
    testTurtle->cw = 0;
    assert(Items(testTurtle) == true);

    strcpy(testTurtle->wds[0], "{}");
    testTurtle->cw = 0;
    assert(Items(testTurtle) == false);

    // Test for <LST> function
    strcpy(testTurtle->wds[0], "{");
    strcpy(testTurtle->wds[1], "\"178\"");
    strcpy(testTurtle->wds[2], "$Z");
    strcpy(testTurtle->wds[3], "}");
    testTurtle->cw = 0;
    assert(Lst(testTurtle) == true);

    // Test for <LST> function for false
    //TODO QUESTION: nested list - outer list is {"MAGENTA", {"WHITE", $Y}, $G}
    Program* testTurtle3 = initTurtle(); 
    
    //Empty List: '{}'
    strcpy(testTurtle->wds[0], "{");
    strcpy(testTurtle->wds[1], "}");
    testTurtle->cw = 0;
    assert(Lst(testTurtle) == true);

    //Without closing '}' should fail:
    strcpy(testTurtle3->wds[0], "{");
    strcpy(testTurtle3->wds[1], "\"BLUE\"");
    strcpy(testTurtle3->wds[2], "\"CYAN\"");
    testTurtle3->cw = 0;
    assert(Lst(testTurtle3) == false);

    //Extra varnum after closing brace:
    strcpy(testTurtle->wds[3], "}");
    strcpy(testTurtle->wds[4], "$Z");
    assert(Lst(testTurtle3) == false);

    //Testing for <LOOP>
    Program* testTurtle4 = initTurtle();
    strcpy(testTurtle4->wds[0], "START");
    strcpy(testTurtle4->wds[1], "LOOP");
    strcpy(testTurtle4->wds[2], "C");
    strcpy(testTurtle4->wds[3], "OVER");
    strcpy(testTurtle4->wds[4], "{");
    strcpy(testTurtle4->wds[5], "\"CYAN\"");
    strcpy(testTurtle4->wds[6], "\"GREEN\"");
    strcpy(testTurtle4->wds[7], "\"BLUE\"");
    strcpy(testTurtle4->wds[8], "}");
    strcpy(testTurtle4->wds[9], "COLOUR");
    strcpy(testTurtle4->wds[10], "$C"); //fails here
    strcpy(testTurtle4->wds[11], "FORWARD");
    strcpy(testTurtle4->wds[12], "5");
    strcpy(testTurtle4->wds[13], "RIGHT");
    strcpy(testTurtle4->wds[14], "90");
    strcpy(testTurtle4->wds[15], "END");
    testTurtle4->cw = 1;
    assert(Loop(testTurtle4) == true);

    //Test for <OPS> Function:
    Program* testTurtle6 = initTurtle();
    strcpy(testTurtle6->wds[0], "+");
    testTurtle6->cw = 0;
    assert(Op(testTurtle6) == true);
    strcpy(testTurtle6->wds[1], "-");
    testTurtle6->cw = 1;
    assert(Op(testTurtle6) == true);
    strcpy(testTurtle6->wds[2], "/");
    testTurtle6->cw = 2;
    assert(Op(testTurtle6) == true);
    strcpy(testTurtle6->wds[3], "*");
    testTurtle6->cw = 3;
    assert(Op(testTurtle6) == true);
    strcpy(testTurtle6->wds[4], "++");
    testTurtle6->cw = 4;
    assert(Op(testTurtle6) == false);
    strcpy(testTurtle6->wds[5], "");
    testTurtle6->cw = 5;
    assert(Op(testTurtle6) == false);
    strcpy(testTurtle6->wds[6], "7+");
    testTurtle6->cw = 6;
    assert(Op(testTurtle6) == false);
    strcpy(testTurtle6->wds[7], ">");
    testTurtle6->cw = 7;
    assert(Op(testTurtle6) == false);
    assert(Op(NULL) == false);

    //Test for <PFIX> Function:
    Program* testTurtle7 = initTurtle();
    // Test for ")"
    strcpy(testTurtle7->wds[0], ")");
    testTurtle7->cw = 0;
    assert(Pfix(testTurtle7) == true);

    // Test for <VARNUM> <PFIX>
    strcpy(testTurtle7->wds[0], "5");
    strcpy(testTurtle7->wds[1], ")");
    testTurtle7->cw = 0;
    assert(Pfix(testTurtle7) == true);

    // Test for <OP> <PFIX>
    strcpy(testTurtle7->wds[0], "+");
    strcpy(testTurtle7->wds[1], "-");
    strcpy(testTurtle7->wds[2], ")");
    testTurtle7->cw = 0;
    assert(Pfix(testTurtle7) == true);

    // Test for non-PFIX string
    strcpy(testTurtle7->wds[0], "?");
    testTurtle7->cw = 0;
    assert(Pfix(testTurtle7) == false);

    // Test for NULL
    assert(Pfix(NULL) == false);

    //Test for <SET> function:
    Program* testTurtle8 = initTurtle();
    strcpy(testTurtle8->wds[0], "SET");
    strcpy(testTurtle8->wds[1], "A");
    strcpy(testTurtle8->wds[2], "(");
    strcpy(testTurtle8->wds[3], "1");
    strcpy(testTurtle8->wds[4], "+");
    strcpy(testTurtle8->wds[5], "2");
    strcpy(testTurtle8->wds[6], ")");
    testTurtle8->cw = 0;
    assert(Set(testTurtle8) == true);

    free(testTurtle);
    free(testTurtle2);
    free(testTurtle3);
    free(testTurtle4);
    free(testTurtle6);
    free(testTurtle7);
    free(testTurtle8);
    free(testLtr);
}

//Blackbox Test 1:
void test_openFile(void){
    printf("Testing openFile\n");
    FILE* testFTTL = openFile("existing_file.txt");
    assert(testFTTL != NULL);
    fclose(testFTTL);
}

//Blackbox Test 2:
void test_initTurtle(void) {
    printf("Testing initTurtle...\n");
    Program* turtle = initTurtle();
    assert(turtle != NULL);
    free(turtle);
}

//Blackbox Test 3:
void test_readWords(void) {
    printf("Testing readWords...\n");
    Program* turtle = initTurtle();
    FILE* file = fopen("existing_file.txt", "r");
    readWords(file, turtle);
    // Check that the first word is as expected
    assert(strcmp(turtle->wds[0], "EXPECTED_FIRST_WORD") == 0);
    fclose(file);
    free(turtle);
}

//Blackbox Test 4:
void test_runProgram(void) {
    printf("Testing runProgram...\n");
    Program* turtle = initTurtle();
    strcpy(turtle->wds[0], "START");
    strcpy(turtle->wds[1], "END");
    runProgram(turtle);
    // If the program has grammar mistakes, it should exit, so if we reach this point, the test has passed
    free(turtle);
}

//Blackbox Test 5:
void test_Prog(void) {
    printf("Testing Prog...\n");
    Program* turtle = initTurtle();
    // Test 1: START statement at the beginning
    strcpy(turtle->wds[0], "START");
    assert(Prog(turtle) == true);
    // Test 2: No START statement at the beginning
    strcpy(turtle->wds[0], "END");
    assert(Prog(turtle) == false);
    free(turtle);
}
