#!/usr/bin/bash

# Runing makeruncom and setting var $1 -> output_file
$1 > Turtle/myResults/output_file

# Compare myOut with Neill Results (TODO just .txt)
diff -q Turtle/myResults/output_file Turtle/Results/expected_output_file

# Check the exit status of the diff command
if [ $? -eq 0 ]
then
    echo "Test passed: The files are identical."
else
    echo "Test failed: The files are different."
fi