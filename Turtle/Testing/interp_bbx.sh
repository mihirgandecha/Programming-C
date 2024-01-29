#!/usr/bin/bash

$1 > Turtle/myResults/output_file

diff -q Turtle/myResults/output_file Turtle/Results/expected_output_file

if [ $? -eq 0 ]
then
    echo "Test passed: The files are identical."
else
    echo "Test failed: The files are different."
fi