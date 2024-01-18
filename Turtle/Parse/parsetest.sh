#!/bin/bash

# Test validArgs
./program 1 2 3
if [ $? -eq 1 ]; then
    echo "validArgs test passed"
else
    echo "validArgs test failed"
fi

# Test validArgs with correct number of arguments
./program 1 2
if [ $? -eq 0 ]; then
    echo "validArgs test passed"
else
    echo "validArgs test failed"
fi

# Test openFile
./program non_existent_file.txt
if [ $? -eq 1 ]; then
    echo "openFile test passed"
else
    echo "openFile test failed"
fi

# Define the functions to test
declare -a functions=("validArgs" "openFile" "initTurtle" "readWords" "runProgram" "Prog" "Inslst" "Ins" "Fwd" "Rgt" "Col" "Loop" "Set" "Varnum" "Num" "Var" "Ltr" "Word" "Item" "Items" "Lst" "checkNull" "Op" "Pfix")

# Loop over the functions
for function in "${functions[@]}"; do
    # Run the program with the function as an argument
    output=$(./program $function)

    # Check for ERROR messages
    if [[ $output == *"ERROR"* ]]; then
        echo "ERROR message in function $function"
    fi

    # Check for EXIT_FAILURE messages
    if [[ $output == *"EXIT_FAILURE"* ]]; then
        echo "EXIT_FAILURE message in function $function"
    fi

    # Check for DEBUG messages
    if [[ $output == *"DEBUG"* ]]; then
        echo "DEBUG message in function $function"
    fi

done