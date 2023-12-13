#!/bin/bash

# Define paths
TTLS_DIR="TTLs"
TESTING_DIR="Testing"
WORKING_TEST_DIR="${TESTING_DIR}/Working_Test"
NOT_WORKING_TEST_DIR="${TESTING_DIR}/Not_Working"

PROGRAM="./your_program" # Replace with your program's executable

# Create Working_Test and Not_Working directories if they do not exist
mkdir -p "${WORKING_TEST_DIR}"
mkdir -p "${NOT_WORKING_TEST_DIR}"

# Clear the contents of Working_Test and Not_Working directories
rm -f "${WORKING_TEST_DIR}"/*
rm -f "${NOT_WORKING_TEST_DIR}"/*

# Loop through each .ttl file in the TTLS directory
for ttl_file in ${TTLS_DIR}/*.ttl; do
    echo "Testing ${ttl_file}..."

    # Redirect TTL file as input to your program
    ${PROGRAM} < "${ttl_file}"
    result=$?

    # Check the result of the test
    if [ ${result} -eq 0 ]; then
        echo "Test passed. Copying ${ttl_file} to ${WORKING_TEST_DIR}"
        cp "${ttl_file}" "${WORKING_TEST_DIR}/"
    else
        echo "Test failed for ${ttl_file}. Copying to ${NOT_WORKING_TEST_DIR}"
        cp "${ttl_file}" "${NOT_WORKING_TEST_DIR}/"
    fi
done
