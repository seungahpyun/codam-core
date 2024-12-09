#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Executable and test files
PIPEX="./pipex_bonus"
INPUT_FILE="input.txt"
OUTPUT_FILE="output.txt"
EXPECTED_FILE="expected.txt"
HERE_DOC_FILE="here_doc_out.txt"

# Cleanup function
cleanup() {
    rm -f "$INPUT_FILE" "$OUTPUT_FILE" "$EXPECTED_FILE" "$HERE_DOC_FILE"
    touch "$OUTPUT_FILE"
    touch "$EXPECTED_FILE"
}

# Error handling
handle_error() {
    echo -e "${RED}Error: $1${NC}"
    cleanup
    exit 1
}

# Test setup
setup_test_files() {
    echo "Hello World!" > "$INPUT_FILE"
    echo "This is a test file" >> "$INPUT_FILE"
    echo "Testing multiple pipes" >> "$INPUT_FILE"
    echo "1234567890" >> "$INPUT_FILE"
    echo "ABCDEFGHIJKLMNOPQRSTUVWXYZ" >> "$INPUT_FILE"
}

# Function to compare outputs
compare_outputs() {
    if diff "$OUTPUT_FILE" "$EXPECTED_FILE" > /dev/null; then
        echo -e "${GREEN}Test passed!${NC}"
        return 0
    else
        echo -e "${RED}Test failed!${NC}"
        echo -e "${YELLOW}Expected output:${NC}"
        cat "$EXPECTED_FILE"
        echo -e "${YELLOW}Your output:${NC}"
        cat "$OUTPUT_FILE"
        echo -e "${YELLOW}Diff:${NC}"
        diff "$EXPECTED_FILE" "$OUTPUT_FILE"
        return 1
    fi
}

# Test multiple pipes
test_multiple_pipes() {
    echo -e "\n${YELLOW}Testing multiple pipes...${NC}"

    # Test 1: Three commands
    echo -e "\nTest 1: cat | grep | wc"
    > "$OUTPUT_FILE"
    > "$EXPECTED_FILE"
    < "$INPUT_FILE" cat | grep a | wc -l > "$EXPECTED_FILE"
    "$PIPEX" "$INPUT_FILE" "cat" "grep a" "wc -l" "$OUTPUT_FILE"
    compare_outputs

    # Test 2: Four commands with simplified tr
    echo -e "\nTest 2: cat | grep | tr | wc"
    > "$OUTPUT_FILE"
    > "$EXPECTED_FILE"
    < "$INPUT_FILE" cat | grep e | tr e E | wc -l > "$EXPECTED_FILE"
    "$PIPEX" "$INPUT_FILE" "cat" "grep e" "tr e E" "wc -l" "$OUTPUT_FILE"
    compare_outputs

    # Test 3: Path commands with simplified tr
    echo -e "\nTest 3: Multiple path commands"
    > "$OUTPUT_FILE"
    > "$EXPECTED_FILE"
    < "$INPUT_FILE" /bin/cat | /usr/bin/grep e | /usr/bin/tr e E > "$EXPECTED_FILE"
    "$PIPEX" "$INPUT_FILE" "/bin/cat" "/usr/bin/grep e" "/usr/bin/tr e E" "$OUTPUT_FILE"
    compare_outputs
}

# Test here_doc functionality
test_heredoc() {
    echo -e "\n${YELLOW}Testing here_doc...${NC}"

    # Test 1: Basic here_doc
    echo -e "\nTest 1: Basic here_doc"
    > "$OUTPUT_FILE"
    > "$EXPECTED_FILE"
    cat << EOF | grep line | wc -l > "$EXPECTED_FILE"
line 1
line 2
line 3
EOF
    "$PIPEX" here_doc LIMITER "grep line" "wc -l" "$OUTPUT_FILE" << EOF
line 1
line 2
line 3
LIMITER
EOF
    compare_outputs

    # Test 2: here_doc with tr (single character translation)
    echo -e "\nTest 2: here_doc with multiple commands"
    > "$OUTPUT_FILE"
    > "$EXPECTED_FILE"
    cat << EOF | grep line | tr l L > "$EXPECTED_FILE"
line 1
line 2
line 3
EOF
    "$PIPEX" here_doc LIMITER "grep line" "tr l L" "$OUTPUT_FILE" << EOF
line 1
line 2
line 3
LIMITER
EOF
    compare_outputs
}

# Main test execution
main() {
    # Check if pipex_bonus executable exists
    if [ ! -f "$PIPEX" ]; then
        handle_error "pipex_bonus executable not found"
    fi

    # Initial cleanup
    cleanup

    # Create test files
    setup_test_files

    # Run tests
    test_multiple_pipes
    test_heredoc

    # Final cleanup
    cleanup

    echo -e "\n${GREEN}All tests completed!${NC}"
}

# Run main function
main
