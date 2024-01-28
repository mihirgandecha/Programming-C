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
make run_parseTTLs
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

sleep 1
echo "TEST[4] initTurtle test --Running ./init_turtle_test..."
./parse_s TTLs/empty.ttl
if [ $? -eq 0 ]; then
    echo "TEST[4] PASSED! initTurtle test passed"
else
    echo "TEST[4] FAILED! initTurtle test failed"
    read -p "Press any key to continue... " -n1 -s
fi
sleep 1

sleep 1
echo "TEST[5] Running blackbox assert test for parser using make parse_assert..."
echo "expect silent for PASS"
make parse_assert > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "TEST[5] PASSED! Assert test passed"
else
    echo "TEST[5] FAILED! Assert test failed"
    read -p "Press any key to continue... " -n1 -s
fi

sleep 1
echo "Testing EXIT completed! Running make clean..."
make clean
if [ $? -eq 0 ]; then
    echo "make clean completed successfully, moving on to running blackbox assert test for parser"
else
    echo "make clean failed, cannot proceed to running blackbox assert test for parser"
    exit 1
fi

echo "Parser test completed, paused to read test output or press any key to continue"
read -p "" -n1 -s