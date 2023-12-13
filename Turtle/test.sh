#!/bin/bash

# Define paths
TTLS_DIR="TTLs"
PROGRAM="./your_program" # Replace with your program's executable

# Compile the program using Makefile
make parse_s

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed, exiting script."
    exit 1
fi

PROGRAM="./parse_s" # Path to the compiled program

# Function to check for unimplemented commands
contains_unimplemented_command() {
    grep -E "LOOP" "$1" > /dev/null
    return $?
}

# Loop through each .ttl file in the TTLS directory
for ttl_file in ${TTLS_DIR}/*.ttl; do
    echo "Testing ${ttl_file}..."

    # Check if the TTL file contains unimplemented commands
    if contains_unimplemented_command "${ttl_file}"; then
        echo "FAIL (Unimplemented command found)"
    else
        # Run the program with the current TTL file
        ${PROGRAM} < "${ttl_file}"
        result=$?

        # Check the result of the test
        if [ ${result} -eq 0 ]; then
            echo "PASS"
        else
            echo "FAIL"
        fi
    fi
done
