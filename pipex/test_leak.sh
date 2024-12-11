#!/bin/bash

echo "=== Testing Memory Leaks and Error Cases ==="

# Function to run valgrind test
run_valgrind_test() {
    local test_name="$1"
    local command="$2"
    echo "Testing: $test_name"
    valgrind --leak-check=full \
             --log-file=valgrind-out.txt \
             --track-fds=yes \
             --trace-children=yes \
             $command

    if grep -q "definitely lost: [1-9]" valgrind-out.txt || \
       grep -q "indirectly lost: [1-9]" valgrind-out.txt; then
        echo "❌ Memory leak detected in $test_name"
        cat valgrind-out.txt
    else
        if grep -q "ERROR SUMMARY: [1-9]" valgrind-out.txt; then
            echo "❌ Errors found in $test_name"
            cat valgrind-out.txt
        else
            echo "✅ No memory leaks in $test_name"
        fi
    fi
}

# Create test files
echo "Creating test files..."
echo "Hello World" > infile.txt
echo "This is a test file" >> infile.txt

# Test 1: Basic functionality with valid inputs
echo "=== Test 1: Basic Functionality ==="
run_valgrind_test "Basic pipe" "./pipex infile.txt 'cat' 'grep Hello' outfile.txt"

# Test 2: Non-existent input file
echo "=== Test 2: Non-existent Input File ==="
run_valgrind_test "Non-existent input" "./pipex nonexistent.txt 'cat' 'grep Hello' outfile.txt"

# Test 3: Invalid command
echo "=== Test 3: Invalid Command ==="
run_valgrind_test "Invalid command" "./pipex infile.txt 'invalidcmd' 'wc -l' outfile.txt"

# Test 4: Permission denied
echo "=== Test 4: Permission Denied ==="
touch noperm.txt
chmod 000 noperm.txt
run_valgrind_test "Permission denied" "./pipex noperm.txt 'cat' 'wc -l' outfile.txt"
chmod 666 noperm.txt

# Test 5: Empty command
echo "=== Test 5: Empty Command ==="
run_valgrind_test "Empty command" "./pipex infile.txt '' 'wc -l' outfile.txt"

# Test 6: Command with quotes
echo "=== Test 6: Command with Quotes ==="
run_valgrind_test "Quoted command" "./pipex infile.txt 'grep \"Hello\"' 'wc -l' outfile.txt"

# Test 7: Multiple spaces in command
echo "=== Test 7: Multiple Spaces ==="
run_valgrind_test "Multiple spaces" "./pipex infile.txt 'cat   -e' 'wc    -l' outfile.txt"

# Bonus part tests (if implemented)
echo "=== Bonus Part Tests ==="

# Test 8: Here_doc
echo "=== Test 8: Here_doc ==="
run_valgrind_test "Here_doc" "echo -e \"test line 1\ntest line 2\nEOF\" | ./pipex_bonus here_doc EOF 'cat' 'wc -l' outfile.txt"

# Cleanup
echo "=== Cleaning up ==="
rm -f infile.txt outfile.txt noperm.txt valgrind-out.txt

echo "=== All tests completed ==="



# ---------------------------------------------------------------
# # Basic test
# valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex infile.txt "ls -l" "wc -l" outfile.txt

# # Test with quotes
# valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex infile.txt "grep 'test'" "wc -l" outfile.txt

# # Test invalid command
# valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex infile.txt "invalidcmd" "wc -l" outfile.txt

# # For bonus part
# # Test here_doc
# echo -e "test line 1\ntest line 2\nEOF" | valgrind --leak-check=full --track-fds=yes --trace-children=yes ./pipex_bonus here_doc EOF "cat" "wc -l" outfile.txt
# # Test multiple pipes
# echo "test line 1" > infile.txt
# echo "test line 2" >> infile.txt
# valgrind --leak-check=full ./pipex_bonus infile.txt "ls" "grep test" "wc -l" outfile.txt
