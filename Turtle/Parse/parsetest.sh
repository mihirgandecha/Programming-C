#!/bin/bash
# Reference: exit_status=$?

echo "Script for blackbox testing TTL files valid, whitebox testing exit for parser..."
sleep 1.5
echo "Script will fail if error found..."
sleep 1
echo "STARTING TEST..."
sleep 1

echo "TEST[1] Running through .ttl files..."
sleep 1
make run_parsetest
if [ $? -eq 0 ]; then
    echo "TEST[1] PASSED! All .ttl parsed successfully."
else
    echo "TEST[1] FAILED! Some files failed to parse"
    read -p "Press any key to continue... " -n1 -s
fi

sleep 1
echo "TEST[2] Args test --Running ./parse_s TTLs/empty.ttl..."
./parse_s TTLs/empty.ttl
if [ $? -eq 0 ]; then
    echo "TEST[2] PASSED! validArgs test passed"
else
    echo "TEST[2] FAILED! validArgs test failed"
    read -p "Press any key to continue... " -n1 -s
fi
sleep 1

sleep 1
echo "TEST[3] Testing error given .txt file as argc[1]"
./parse_s non_existent_file.ttx
if [ $? -eq 1 ]; then
    echo "TEST[3] PASSED! openFile test passed"
else
    echo "TEST[3] FAILED! openFile test failed"
    read -p "Press any key to continue... " -n1 -s
fi
sleep 1

# # Define the functions to test
# declare -a functions=("validArgs" "openFile" "initTurtle" "readWords" "runProgram" "Prog" "Inslst" "Ins" "Fwd" "Rgt" "Col" "Loop" "Set" "Varnum" "Num" "Var" "Ltr" "Word" "Item" "Items" "Lst" "checkNull" "Op" "Pfix")

# # Loop over the functions
# for function in "${functions[@]}"; do
#     # Run the program with the function as an argument
#     output=$(./program $function)

#     # Check for ERROR messages
#     if [[ $output == *"ERROR"* ]]; then
#         echo "ERROR message in function $function"
#     fi

#     # Check for EXIT_FAILURE messages
#     if [[ $output == *"EXIT_FAILURE"* ]]; then
#         echo "EXIT_FAILURE message in function $function"
#     fi

#     # Check for DEBUG messages
#     if [[ $output == *"DEBUG"* ]]; then
#         echo "DEBUG message in function $function"
#     fi

# done