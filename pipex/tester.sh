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
    
    # Compare exit codes
    if [ $SHELL_STATUS -eq $PIPEX_STATUS ]; then
        echo -e "${GREEN}Exit codes match ✓${NC}"
    else
        echo -e "${RED}Exit codes differ ($SHELL_STATUS vs $PIPEX_STATUS) ✗${NC}"
    fi
    
    # Compare outputs
    if diff shell_out pipex_out >/dev/null 2>&1; then
        echo -e "${GREEN}Outputs match ✓${NC}"
    else
        echo -e "${RED}Outputs differ ✗${NC}"
        echo "Expected output:"
        cat shell_out
        echo "Your output:"
        cat pipex_out
    fi
}

# Setup
make
mkdir -p test_files
printf "Hello World\nThis is a test\nLine 3\n" > test_files/input.txt
printf "Random\nData\nFor\nTesting\n" > test_files/random.txt

# Basic tests
run_test test_files/input.txt "cat" "wc -l" "basic cat and wc"
run_test test_files/input.txt "grep test" "wc -w" "grep and wc"
run_test test_files/random.txt "sort" "uniq" "sort and uniq"

# Complex commands with properly escaped quotes
run_test test_files/input.txt "sed s/test/check/" "grep check" "sed and grep"
run_test test_files/random.txt "tr [:lower:] [:upper:]" "sort -r" "tr and sort"

# Error handling tests
echo -e "\n=== Error Handling Tests ==="
echo "Testing non-existent input file..."
./pipex "nonexistent.txt" "cat" "wc" out 2>/dev/null
[ $? -ne 0 ] && echo -e "${GREEN}Error handled correctly ✓${NC}" || echo -e "${RED}Error not handled ✗${NC}"

# echo "Testing invalid command..."
# ./pipex test_files/input.txt "nonexistentcmd123" "wc" out 2>/dev/null
# [ $? -ne 0 ] && echo -e "${GREEN}Error handled correctly ✓${NC}" || echo -e "${RED}Error not handled ✗${NC}"

echo "Testing invalid command..."
./pipex test_files/input.txt "nonexistentcmd123" "wc" out 2> error_log
EXIT_CODE=$?

if [ $EXIT_CODE -eq 127 ]; then
    echo -e "${GREEN}Error handled correctly (Command not found) ✓${NC}"
elif [ $EXIT_CODE -eq 126 ]; then
    echo -e "${GREEN}Error handled correctly (Cannot execute) ✓${NC}"
else
    echo -e "${RED}Error not handled ✗ (exit code $EXIT_CODE)${NC}"
    echo "Error log:"
    cat error_log
fi






# Cleanup
rm -f shell_out shell_err pipex_out pipex_err out
rm -rf test_files

echo -e "\nAll tests completed."

# ------------------------------------part2--------------------------------------------
# RED='\033[0;31m'
# GREEN='\033[0;32m'
# BLUE='\033[0;34m'
# NC='\033[0m'

# # Create test files
# echo "This is test file content" > infile
# echo -e "apple\nbanana\napple pie\norange" > infile2
# echo "Test with spaces and special chars: $#@!" > infile3

# # Cleanup function
# cleanup() {
#     rm -f outfile outfile_shell test_outfile infile infile2 infile3
# }

# # Test function
# run_test() {
#     local test_name="$1"
#     local infile="$2"
#     local cmd1="$3"
#     local cmd2="$4"
    
#     ./pipex "$infile" "$cmd1" "$cmd2" "test_outfile"
#     pipex_exit=$?
    
#     eval "< $infile $cmd1 | $cmd2 > outfile_shell"
#     shell_exit=$?
    
#     if diff test_outfile outfile_shell > /dev/null && [ $pipex_exit -eq $shell_exit ]; then
#         printf "${GREEN}[OK]${NC} %s\n" "$test_name"
#     else
#         printf "${RED}[KO]${NC} %s\n" "$test_name"
#         echo "Expected output (shell):"
#         cat outfile_shell
#         echo "Your output (pipex):"
#         cat test_outfile
#         echo "Shell exit code: $shell_exit"
#         echo "Pipex exit code: $pipex_exit"
#     fi
# }

# # Error handling tests
# test_errors() {
#     printf "\n${BLUE}Testing error handling:${NC}\n"
    
#     ./pipex "nonexistent" "ls" "wc" "test_outfile" 2>/dev/null
#     local exit_code=$?
#     if [ $exit_code -ne 0 ]; then
#         printf "${GREEN}[OK]${NC} Non-existent input file (exit code: $exit_code)\n"
#     else
#         printf "${RED}[KO]${NC} Non-existent input file (exit code: $exit_code)\n"
#     fi
    
#     ./pipex "infile" "invalidcmd" "wc" "test_outfile" 2>/dev/null
#     exit_code=$?
#     if [ $exit_code -ne 0 ]; then
#         printf "${GREEN}[OK]${NC} Invalid command (exit code: $exit_code)\n"
#     else
#         printf "${RED}[KO]${NC} Invalid command (exit code: $exit_code)\n"
#     fi
    
#     ./pipex "infile" "ls" "outfile" 2>/dev/null
#     exit_code=$?
#     if [ $exit_code -ne 0 ]; then
#         printf "${GREEN}[OK]${NC} Wrong number of arguments (exit code: $exit_code)\n"
#     else
#         printf "${RED}[KO]${NC} Wrong number of arguments (exit code: $exit_code)\n"
#     fi
# }

# printf "${BLUE}Starting pipex tests...${NC}\n\n"

# # Basic tests
# run_test "Basic test" "infile" "cat" "grep test"
# run_test "grep | wc" "infile2" "grep apple" "wc -l"
# run_test "cat | grep" "infile3" "cat" "grep special"

# # Complex tests
# run_test "Multiple spaces" "infile" "tr ' ' '_'" "tr '_' '-'"
# run_test "Special characters" "infile3" "grep '$'" "wc -w"
# run_test "Quoted arguments" "infile2" "grep 'apple pie'" "wc -l"

# # Error tests
# test_errors

# # Cleanup
# cleanup

# printf "\n${BLUE}Tests completed.${NC}\n"
