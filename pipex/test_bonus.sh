#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

function run_test() {
    local infile="$1"
    local cmd1="$2"
    local cmd2="$3"
    local test_name="$4"

    echo -e "\n=== Test $test_name ==="
    echo "Command: < $infile $cmd1 | $cmd2"

    # Run shell command
    eval "< $infile $cmd1 | $cmd2" > shell_out 2> shell_err
    SHELL_STATUS=$?

    # Run pipex
    ./pipex "$infile" "$cmd1" "$cmd2" pipex_out 2> pipex_err
    PIPEX_STATUS=$?

    # Compare output files
    if diff shell_out pipex_out >/dev/null 2>&1; then
        echo -e "${GREEN}Outputs match ✓${NC}"
    else
        echo -e "${RED}Outputs differ ✗${NC}"
        echo "Expected output:"
        cat shell_out
        echo "Your output:"
        cat pipex_out
    fi

    # For errors, just check if both return non-zero status
    if [ $SHELL_STATUS -eq 0 ] && [ $PIPEX_STATUS -eq 0 ]; then
        echo -e "${GREEN}Both commands succeeded ✓${NC}"
    elif [ $SHELL_STATUS -ne 0 ] && [ $PIPEX_STATUS -ne 0 ]; then
        echo -e "${GREEN}Both commands failed as expected ✓${NC}"
    else
        echo -e "${RED}Exit status mismatch (shell: $SHELL_STATUS, pipex: $PIPEX_STATUS) ✗${NC}"
    fi
}

# Setup
make
mkdir -p test_files
printf "Hello World\nThis is a test\nLine 3\n" > test_files/input.txt
printf "Random\nData\nFor\nTesting\n" > test_files/random.txt
echo "Creating test files..." > test_files/with_permission
chmod 000 test_files/with_permission

# Basic functionality tests
echo -e "\n=== Basic Functionality Tests ==="
run_test test_files/input.txt "cat" "wc -l" "basic cat and wc"
run_test test_files/input.txt "grep test" "wc -w" "grep and wc"
run_test test_files/random.txt "sort" "uniq" "sort and uniq"

# Error handling tests
echo -e "\n=== Error Handling Tests ==="
echo "Testing non-existent input file..."
./pipex "nonexistent.txt" "cat" "wc" out 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}Error handled correctly ✓${NC}"
else
    echo -e "${RED}Error not handled ✗${NC}"
fi

echo "Testing invalid command..."
./pipex test_files/input.txt "invalidcmd" "wc" out 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}Error handled correctly ✓${NC}"
else
    echo -e "${RED}Error not handled ✗${NC}"
fi

echo "Testing file permission denied..."
./pipex test_files/with_permission "cat" "wc" out 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}Error handled correctly ✓${NC}"
else
    echo -e "${RED}Error not handled ✗${NC}"
fi

# Arguments test
echo -e "\n=== Arguments Test ==="
echo "Testing incorrect number of arguments..."
./pipex "file1" "cmd1" out 2>/dev/null
if [ $? -ne 0 ]; then
    echo -e "${GREEN}Error handled correctly ✓${NC}"
else
    echo -e "${RED}Error not handled ✗${NC}"
fi

# Cleanup
rm -f shell_out shell_err pipex_out pipex_err out
rm -rf test_files

echo -e "\nAll tests completed."
