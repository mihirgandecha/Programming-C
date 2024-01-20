#!/bin/bash

# Define paths
TTLS_DIR="TTLs"

# Compile the program using Makefile
make parse_s
PROGRAM="./parse_s" # Replace with your program's executable

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed, exiting script."
    exit 1
fi

# Arrays to store test results
passed_tests=()
failed_tests=()

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
        failed_tests+=("${ttl_file}")
    else
        # Run the program with the current TTL file
        ${PROGRAM} < "${ttl_file}"
        result=$?

        # Check the result of the test
        if [ ${result} -eq 0 ]; then
            echo "PASS"
            passed_tests+=("${ttl_file}")
        else
            echo "FAIL"
            failed_tests+=("${ttl_file}")
        fi
    fi
done

# Print summary
echo "Test Summary:"
echo "Passed Tests:"
for test in "${passed_tests[@]}"; do
    echo "  - ${test}"
done

echo "Failed Tests:"
for test in "${failed_tests[@]}"; do
    echo "  - ${test}"
done
