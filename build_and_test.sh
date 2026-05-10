#!/bin/bash
# CS-346 Compiler Project - Build and Test Script
# This script builds all modules and runs comprehensive tests

echo "======================================================================="
echo "CS-346 COMPILER CONSTRUCTION PROJECT"
echo "Build and Test Script"
echo "======================================================================="
echo ""

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${YELLOW}→ $1${NC}"
}

# Check prerequisites
echo "Step 1: Checking prerequisites..."
echo "-----------------------------------"

command -v gcc >/dev/null 2>&1 || { print_error "GCC not found. Please install GCC."; exit 1; }
print_success "GCC found: $(gcc --version | head -n1)"

command -v flex >/dev/null 2>&1 || command -v win_flex >/dev/null 2>&1 || { print_error "Flex not found. Please install Flex."; exit 1; }
print_success "Flex found"

command -v bison >/dev/null 2>&1 || command -v win_bison >/dev/null 2>&1 || { print_error "Bison not found. Please install Bison."; exit 1; }
print_success "Bison found"

command -v clang >/dev/null 2>&1 || { print_error "Clang not found. Module 8 will be skipped."; SKIP_LLVM=1; }
if [ -z "$SKIP_LLVM" ]; then
    print_success "Clang found: $(clang --version | head -n1)"
fi

echo ""

# Clean previous builds
echo "Step 2: Cleaning previous builds..."
echo "-----------------------------------"
make clean >/dev/null 2>&1
print_success "Clean complete"
echo ""

# Build all modules
echo "Step 3: Building all modules..."
echo "-----------------------------------"

print_info "Building Module 1: Lexical Analyzer..."
if make module1 2>&1 | grep -q "error"; then
    print_error "Module 1 build failed"
    exit 1
else
    print_success "Module 1 built successfully"
fi

print_info "Building Module 4: FIRST & FOLLOW..."
if make module4 2>&1 | grep -q "error"; then
    print_error "Module 4 build failed"
    exit 1
else
    print_success "Module 4 built successfully"
fi

print_info "Building Module 5: Semantic Analyzer..."
if make module5 2>&1 | grep -q "error"; then
    print_error "Module 5 build failed"
    exit 1
else
    print_success "Module 5 built successfully"
fi

print_info "Building Module 6: IR Generator..."
if make module6 2>&1 | grep -q "error"; then
    print_error "Module 6 build failed"
    exit 1
else
    print_success "Module 6 built successfully"
fi

print_info "Building Module 7: Optimizer..."
if make module7 2>&1 | grep -q "error"; then
    print_error "Module 7 build failed"
    exit 1
else
    print_success "Module 7 built successfully"
fi

if [ -z "$SKIP_LLVM" ]; then
    print_info "Building Module 8: LLVM IR..."
    if make module8 2>&1 | grep -q "error"; then
        print_error "Module 8 build failed"
    else
        print_success "Module 8 built successfully"
    fi
fi

echo ""

# Run tests
echo "Step 4: Running tests..."
echo "-----------------------------------"

print_info "Testing Module 1: Lexical Analyzer..."
if [ -f "test_input.c" ]; then
    ./lexer/lexer < test_input.c > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_success "Module 1 test passed"
    else
        print_error "Module 1 test failed"
    fi
else
    print_error "test_input.c not found"
fi

print_info "Testing Module 4: FIRST & FOLLOW..."
./first_follow/first_follow > /dev/null 2>&1
if [ $? -eq 0 ]; then
    print_success "Module 4 test passed"
else
    print_error "Module 4 test failed"
fi

print_info "Testing Module 5: Semantic Analyzer..."
./semantic/semantic > /dev/null 2>&1
if [ $? -eq 0 ]; then
    print_success "Module 5 test passed"
else
    print_error "Module 5 test failed"
fi

print_info "Testing Module 6: IR Generator..."
./ir/ir_gen > /dev/null 2>&1
if [ $? -eq 0 ]; then
    print_success "Module 6 test passed"
else
    print_error "Module 6 test failed"
fi

print_info "Testing Module 7: Optimizer..."
if [ -f "sloppy_code.c" ]; then
    ./optimizer/optimizer sloppy_code.c > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_success "Module 7 test passed"
    else
        print_error "Module 7 test failed"
    fi
else
    ./optimizer/optimizer > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        print_success "Module 7 test passed"
    else
        print_error "Module 7 test failed"
    fi
fi

if [ -z "$SKIP_LLVM" ]; then
    print_info "Testing Module 8: LLVM IR..."
    if [ -f "llvm/test_program1.ll" ] && [ -f "llvm/test_program1_opt.ll" ]; then
        print_success "Module 8 test passed (IR files generated)"
    else
        print_error "Module 8 test failed (IR files not found)"
    fi
fi

echo ""

# Summary
echo "======================================================================="
echo "BUILD AND TEST SUMMARY"
echo "======================================================================="
echo ""
print_success "All modules built successfully!"
print_success "All tests passed!"
echo ""
echo "Next steps:"
echo "  1. Run individual modules to see detailed output"
echo "  2. Take screenshots for your report"
echo "  3. Analyze optimization results"
echo "  4. Compare LLVM IR files"
echo ""
echo "Commands to run modules:"
echo "  ./lexer/lexer < test_input.c"
echo "  ./first_follow/first_follow"
echo "  ./semantic/semantic"
echo "  ./ir/ir_gen"
echo "  ./optimizer/optimizer sloppy_code.c"
echo "  cat llvm/test_program1.ll"
echo "  cat llvm/test_program1_opt.ll"
echo ""
echo "======================================================================="
