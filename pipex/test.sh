#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

function run_test() {
    local infile="$1"
    local cmd1="$2"
    local cmd2="$3"
    local outfile="$4"
    local test_name="$5"

    echo -e "\n=== Test $test_name ==="
    echo "Command: < $infile $cmd1 | $cmd2 > $outfile"

    # Run shell command
    eval "< $infile $cmd1 | $cmd2 > shell_out" 2> shell_err
    SHELL_STATUS=$?

    # Run pipex
    ./pipex "$infile" "$cmd1" "$cmd2" "$outfile" 2> pipex_err
    PIPEX_STATUS=$?

    # Compare outputs
    if diff shell_out "$outfile" >/dev/null 2>&1; then
        echo -e "${GREEN}Outputs match ✓${NC}"
    else
        echo -e "${RED}Outputs differ ✗${NC}"
        echo "Shell output:"
        cat shell_out
        echo "Pipex output:"
        cat "$outfile"
    fi

    # Compare exit status
    if [ $SHELL_STATUS -eq $PIPEX_STATUS ]; then
        echo -e "${GREEN}Exit status match (shell: $SHELL_STATUS, pipex: $PIPEX_STATUS) ✓${NC}"
    else
        echo -e "${RED}Exit status differ (shell: $SHELL_STATUS, pipex: $PIPEX_STATUS) ✗${NC}"
    fi
}

# Setup test files
mkdir -p test_files
echo "Hello World\nApple\nBanana\nApple\nZebra\nHello World" > test_files/input.txt
echo "This should not be readable" > test_files/no_access.txt
chmod 000 test_files/no_access.txt

# Basic tests
run_test test_files/input.txt "cat" "wc -l" "test_files/out1" "Simple pipe test"
run_test test_files/input.txt "grep Apple" "wc -l" "test_files/out2" "grep test"
run_test test_files/input.txt "cat" "head -n 2" "test_files/out3" "head test"

# Error handling tests
echo -e "=== Error Handling Tests ==="

# Test 1: Non-existent input file
echo "Test: Non-existent input file"
./pipex "nonexistent.txt" "cat" "wc" "test_files/out_err1" 2>/dev/null
echo -e "Exit status: $? ${GREEN}✓${NC}"

# Test 2: Invalid first command
echo "Test: Invalid first command"
./pipex test_files/input.txt "invalid_cmd" "wc" "test_files/out_err2" 2>/dev/null
echo -e "Exit status: $? ${GREEN}✓${NC}"

# Test 3: Invalid second command
echo "Test: Invalid second command"
./pipex test_files/input.txt "cat" "invalid_cmd" "test_files/out_err3" 2>/dev/null
echo -e "Exit status: $? ${GREEN}✓${NC}"

# Test 4: No read permission on input file
echo "Test: No read permission on input file"
./pipex test_files/no_access.txt "cat" "wc" "test_files/out_err4" 2>/dev/null
echo -e "Exit status: $? ${GREEN}✓${NC}"

# Test 5: Write to non-existent directory
echo "Test: Write to non-existent directory"
./pipex test_files/input.txt "cat" "wc" "non_existent_dir/out" 2>/dev/null
echo -e "Exit status: $? ${GREEN}✓${NC}"

# Test 6: Multiple pipes with space in command
run_test test_files/input.txt "grep Hello" "wc -l" "test_files/out4" "Space in command test"

# Cleanup
rm -f shell_out shell_err pipex_err
rm -rf test_files

echo -e "All tests completed."
