# Makefile for CS-346 Compiler Construction Project
# NUST SEECS - BSCS-2023-AB
# Builds all 8 modules of the compiler

# Compiler settings
CC = gcc
CFLAGS = -Wall -g -lm
FLEX = flex
BISON = bison

# Check if on Windows
ifeq ($(OS),Windows_NT)
    FLEX = win_flex
    BISON = win_bison
    RM = del /Q
    RMDIR = rmdir /S /Q
    EXE = .exe
else
    RM = rm -f
    RMDIR = rm -rf
    EXE =
endif

# Targets
all: module1 module4 module5 module6 module7

# Module 1: Lexical Analyzer
module1: lexer/lexer.l
	@echo "=== Building Module 1: Lexical Analyzer ==="
	$(FLEX) -o lexer/lex.yy.c lexer/lexer.l
	$(CC) -o lexer/lexer$(EXE) lexer/lex.yy.c $(CFLAGS)
	@echo "Module 1 built successfully!"

# Module 2 & 3: Parser (requires lexer integration)
module2: parser/parser.y lexer/lexer.l
	@echo "=== Building Module 2 & 3: Parser ==="
	$(BISON) -d -o parser/parser.tab.c parser/parser.y
	$(FLEX) -o lexer/lex.yy.c lexer/lexer.l
	$(CC) -o parser/parser$(EXE) parser/parser.tab.c lexer/lex.yy.c $(CFLAGS)
	@echo "Module 2 & 3 built successfully!"

# Module 4: FIRST & FOLLOW Sets
module4: first_follow/first_follow.c
	@echo "=== Building Module 4: FIRST & FOLLOW Sets ==="
	$(CC) -o first_follow/first_follow$(EXE) first_follow/first_follow.c $(CFLAGS)
	@echo "Module 4 built successfully!"

# Module 5: Semantic Analyzer
module5: semantic/semantic.c
	@echo "=== Building Module 5: Semantic Analyzer ==="
	$(CC) -o semantic/semantic$(EXE) semantic/semantic.c $(CFLAGS)
	@echo "Module 5 built successfully!"

# Module 6: IR Generator
module6: ir/ir_gen.c
	@echo "=== Building Module 6: IR Generator ==="
	$(CC) -o ir/ir_gen$(EXE) ir/ir_gen.c $(CFLAGS)
	@echo "Module 6 built successfully!"

# Module 7: Optimizer
module7: optimizer/optimizer.c
	@echo "=== Building Module 7: Code Optimizer ==="
	$(CC) -o optimizer/optimizer$(EXE) optimizer/optimizer.c $(CFLAGS)
	@echo "Module 7 built successfully!"

# Module 8: LLVM IR Generation
module8:
	@echo "=== Module 8: LLVM IR Generation ==="
	@echo "Generating unoptimized LLVM IR..."
	clang -S -emit-llvm llvm/test_program1.c -o llvm/test_program1.ll
	clang -S -emit-llvm llvm/test_program2.c -o llvm/test_program2.ll
	@echo "Generating optimized LLVM IR (-O3)..."
	clang -S -emit-llvm -O3 llvm/test_program1.c -o llvm/test_program1_opt.ll
	clang -S -emit-llvm -O3 llvm/test_program2.c -o llvm/test_program2_opt.ll
	@echo "Module 8 completed successfully!"

# Run all modules
run: all
	@echo "\n=== Running Module 1: Lexer ==="
	./lexer/lexer$(EXE) < test_input.c
	@echo "\n=== Running Module 4: FIRST & FOLLOW ==="
	./first_follow/first_follow$(EXE)
	@echo "\n=== Running Module 5: Semantic Analyzer ==="
	./semantic/semantic$(EXE)
	@echo "\n=== Running Module 6: IR Generator ==="
	./ir/ir_gen$(EXE)
	@echo "\n=== Running Module 7: Optimizer ==="
	./optimizer/optimizer$(EXE)

# Test individual modules
test-lexer: module1
	@echo "Testing Lexer with test_input.c..."
	./lexer/lexer$(EXE) < test_input.c

test-parser: module2
	@echo "Testing Parser..."
	./parser/parser$(EXE)

test-first-follow: module4
	@echo "Testing FIRST & FOLLOW computation..."
	./first_follow/first_follow$(EXE)

test-semantic: module5
	@echo "Testing Semantic Analyzer..."
	./semantic/semantic$(EXE)

test-ir: module6
	@echo "Testing IR Generator..."
	./ir/ir_gen$(EXE)

test-optimizer: module7
	@echo "Testing Optimizer..."
	./optimizer/optimizer$(EXE) sloppy_code.c

test-llvm: module8
	@echo "LLVM IR files generated in llvm/ directory"
	@echo "View with: cat llvm/*.ll"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
ifeq ($(OS),Windows_NT)
	-$(RM) lexer\lex.yy.c lexer\lexer.exe 2>nul
	-$(RM) parser\parser.tab.c parser\parser.tab.h parser\parser.exe 2>nul
	-$(RM) first_follow\first_follow.exe 2>nul
	-$(RM) semantic\semantic.exe 2>nul
	-$(RM) ir\ir_gen.exe 2>nul
	-$(RM) optimizer\optimizer.exe 2>nul
	-$(RM) llvm\*.ll 2>nul
else
	$(RM) lexer/lex.yy.c lexer/lexer
	$(RM) parser/parser.tab.c parser/parser.tab.h parser/parser
	$(RM) first_follow/first_follow
	$(RM) semantic/semantic
	$(RM) ir/ir_gen
	$(RM) optimizer/optimizer
	$(RM) llvm/*.ll
endif
	@echo "Clean complete!"

# Help
help:
	@echo "CS-346 Compiler Construction Project - Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build all modules"
	@echo "  module1      - Build Lexical Analyzer"
	@echo "  module2      - Build Parser"
	@echo "  module4      - Build FIRST & FOLLOW"
	@echo "  module5      - Build Semantic Analyzer"
	@echo "  module6      - Build IR Generator"
	@echo "  module7      - Build Optimizer"
	@echo "  module8      - Generate LLVM IR"
	@echo "  run          - Build and run all modules"
	@echo "  test-*       - Test individual modules"
	@echo "  clean        - Remove build artifacts"
	@echo "  help         - Show this help message"

.PHONY: all module1 module2 module4 module5 module6 module7 module8 run clean help \
        test-lexer test-parser test-first-follow test-semantic test-ir test-optimizer test-llvm
