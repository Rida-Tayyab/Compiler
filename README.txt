================================================================================
CS-346 COMPILER CONSTRUCTION PROJECT
================================================================================
Course: CS-346 Compiler Construction
Class: BSCS-13B
Institution: NUST SEECS
Instructors: 
  - Lab: Ms. Urooj Akmal
  - Theory: Dr. Ahmed Rathore

================================================================================
PROJECT OVERVIEW
================================================================================
This is a complete mini-compiler implementation consisting of 8 integrated
modules that form a linear compilation pipeline:

1. Lexical Analysis (Flex)
2. Syntax Analysis (Bison)
3. Extended Grammar (Functions, Exponentiation)
4. FIRST & FOLLOW Sets / LL(1) Parsing
5. Semantic Analysis (Type & Scope Checking)
6. Intermediate Representation (Three-Address Code)
7. Code Optimization (5 techniques)
8. LLVM IR Generation

================================================================================
DIRECTORY STRUCTURE
================================================================================
project/
├── lexer/              Module 1: Lexical analyzer (.l file)
├── parser/             Modules 2 & 3: Parser (.y file)
├── first_follow/       Module 4: FIRST/FOLLOW computation
├── semantic/           Module 5: Type and scope checker
├── ir/                 Module 6: IR generator (TAC)
├── optimizer/          Module 7: Optimization passes
├── llvm/               Module 8: LLVM test files and outputs
├── Makefile            Build script
├── README.txt          This file
├── test_input.c        Sample input for testing
├── sloppy_code.c       Unoptimized code example
└── optimized_code.c    Optimized code example

================================================================================
PREREQUISITES
================================================================================
Windows:
  - GCC (MinGW or similar)
  - win_flex (Flex for Windows)
  - win_bison (Bison for Windows)
  - Clang/LLVM (for Module 8)

Linux:
  - GCC
  - Flex
  - Bison
  - Clang/LLVM

Installation (Linux):
  sudo apt-get install gcc flex bison clang llvm

Installation (Windows):
  - Install MinGW-w64
  - Download win_flex and win_bison from GnuWin32
  - Install LLVM from https://releases.llvm.org/

================================================================================
BUILD INSTRUCTIONS
================================================================================

1. Build all modules:
   make all

2. Build individual modules:
   make module1    # Lexical Analyzer
   make module2    # Parser
   make module4    # FIRST & FOLLOW
   make module5    # Semantic Analyzer
   make module6    # IR Generator
   make module7    # Optimizer
   make module8    # LLVM IR Generation

3. Clean build artifacts:
   make clean

4. View help:
   make help

================================================================================
RUNNING THE COMPILER
================================================================================

Run all modules in sequence:
  make run

Test individual modules:
  make test-lexer
  make test-parser
  make test-first-follow
  make test-semantic
  make test-ir
  make test-optimizer
  make test-llvm

Manual execution:
  # Module 1: Lexer
  ./lexer/lexer < test_input.c
  
  # Module 4: FIRST & FOLLOW
  ./first_follow/first_follow
  
  # Module 5: Semantic Analysis
  ./semantic/semantic
  
  # Module 6: IR Generation
  ./ir/ir_gen
  
  # Module 7: Optimizer
  ./optimizer/optimizer sloppy_code.c
  
  # Module 8: LLVM IR
  clang -S -emit-llvm llvm/test_program1.c -o llvm/test_program1.ll
  clang -S -emit-llvm -O3 llvm/test_program1.c -o llvm/test_program1_opt.ll

================================================================================
MODULE DESCRIPTIONS
================================================================================

MODULE 1: LEXICAL ANALYSIS
- Tokenizes source code using Flex
- Recognizes keywords, identifiers, operators, literals
- Handles comments (single-line and multi-line)
- Computes hash values for tokens
- Output: Token table with type, value, line number, hash

MODULE 2 & 3: SYNTAX ANALYSIS
- Parses expressions using Bison (LALR(1))
- Supports infix, prefix, postfix notation
- Extended grammar with exponentiation (right-associative)
- Handles operator precedence and associativity
- Output: Parse tree and evaluation results

MODULE 4: FIRST & FOLLOW SETS
- Computes FIRST sets for all non-terminals
- Computes FOLLOW sets for all non-terminals
- Verifies LL(1) compatibility
- Target grammar: E → T E', T → F T', F → (E) | id | num
- Output: FIRST and FOLLOW sets table

MODULE 5: SEMANTIC ANALYSIS
- Type checking with implicit conversions
- Scope management using scope stack
- Symbol table with scope levels
- Detects: undeclared variables, redeclarations, type mismatches
- Output: Symbol table and error messages

MODULE 6: INTERMEDIATE REPRESENTATION
- Generates Three-Address Code (TAC)
- Supports: arithmetic, control flow, functions, arrays
- TAC forms: x = y op z, goto L, if x goto L, call f
- Output: TAC listing with line numbers

MODULE 7: CODE OPTIMIZATION
Implements 5 optimization techniques:
1. Constant Folding - Evaluate constant expressions at compile time
2. Constant Propagation - Replace variables with constant values
3. Dead Code Elimination - Remove unreachable code
4. Common Subexpression Elimination - Reuse computed values
5. Strength Reduction - Replace expensive ops with cheaper ones

Additional features:
- Control flow analysis for unreachable code detection
- Performance comparison (5 runs, speedup ratio)
- Before/after IR printing

MODULE 8: LLVM IR GENERATION
- Generates LLVM IR using Clang
- Compares unoptimized vs optimized (-O3) IR
- Analyzes LLVM optimizations
- Annotates key instructions: alloca, load, store, ret, add, call
- Output: .ll files (text IR format)

================================================================================
SAMPLE USAGE
================================================================================

Example 1: Tokenize a C file
  ./lexer/lexer < test_input.c

Example 2: Compute FIRST/FOLLOW sets
  ./first_follow/first_follow

Example 3: Check semantics
  ./semantic/semantic

Example 4: Generate IR
  ./ir/ir_gen

Example 5: Optimize code
  ./optimizer/optimizer sloppy_code.c

Example 6: Generate LLVM IR
  clang -S -emit-llvm llvm/test_program1.c -o output.ll
  clang -S -emit-llvm -O3 llvm/test_program1.c -o output_opt.ll

================================================================================
TESTING
================================================================================

Test files provided:
- test_input.c: Comprehensive test with all language features
- sloppy_code.c: Unoptimized code with optimization opportunities
- optimized_code.c: Hand-optimized version for comparison
- llvm/test_program1.c: Simple arithmetic and control flow
- llvm/test_program2.c: Loops and arrays

Expected outputs:
- Module 1: Token table with ~100+ tokens
- Module 4: FIRST/FOLLOW sets for 5 non-terminals
- Module 5: Symbol table with scope levels, type checking results
- Module 6: TAC with ~20+ instructions
- Module 7: Before/after IR, performance speedup ~1.5-3x
- Module 8: .ll files showing LLVM optimizations

================================================================================
TROUBLESHOOTING
================================================================================

Problem: "flex: command not found" or "bison: command not found"
Solution: Install Flex and Bison (see Prerequisites)

Problem: "undefined reference to 'yywrap'"
Solution: Add %option noyywrap to .l file or link with -lfl

Problem: Parser conflicts (shift/reduce, reduce/reduce)
Solution: Check operator precedence declarations in .y file

Problem: "clang: command not found"
Solution: Install LLVM/Clang (see Prerequisites)

Problem: Makefile errors on Windows
Solution: Ensure win_flex and win_bison are in PATH

================================================================================
GRADING CHECKLIST
================================================================================

Module 1: Lexical Analysis [8 marks]
  ✓ .l file with all token patterns
  ✓ Token table output
  ✓ Hash computation
  ✓ Comment handling

Module 2: Parsing [8 marks]
  ✓ .y file with grammar rules
  ✓ Postfix/Prefix/Infix support
  ✓ Parse tree generation
  ✓ Sample outputs

Module 3: Extended Grammar [8 marks]
  ✓ Exponentiation (right-associative)
  ✓ Function support (log, exp)
  ✓ Float handling
  ✓ Error messages

Module 4: FIRST & FOLLOW [8 marks]
  ✓ FIRST set computation
  ✓ FOLLOW set computation
  ✓ LL(1) table
  ✓ Correctness verification

Module 5: Semantic Analysis [8 marks]
  ✓ Type checking
  ✓ Scope checking
  ✓ Symbol table
  ✓ Error detection

Module 6: IR Generation [10 marks]
  ✓ TAC generation
  ✓ All TAC forms supported
  ✓ Sample output
  ✓ Integration with Module 5

Module 7: Optimization [40 marks total]
  ✓ Task 1: Refactoring [5 marks]
  ✓ Task 2: IR printing [5 marks]
  ✓ Task 3: 3-5 optimizations [15 marks]
  ✓ Task 4: Control flow [7 marks]
  ✓ Task 5: Loop optimization [8 marks]
  ✓ Task 6: Performance comparison [5 marks]

Module 8: LLVM [11 marks]
  ✓ Installation verification [5 marks]
  ✓ Unoptimized IR generation
  ✓ Optimized IR generation
  ✓ Comparison and analysis [6 marks]

Integration [7 marks]
  ✓ All modules compile together
  ✓ Modular code structure
  ✓ Makefile provided

================================================================================
REPORT REQUIREMENTS
================================================================================

The report (PDF, minimum 10 pages) must include:
1. Cover page with course info and group members
2. Table of contents
3. Introduction to compiler pipeline
4. Module 1-8 sections with:
   - Explanation of implementation
   - Code snippets
   - Screenshots of output
   - Sample inputs and outputs
5. Performance comparison table (Module 7)
6. LLVM IR comparison (Module 8)
7. Conclusion
8. References

================================================================================
ACADEMIC INTEGRITY
================================================================================

All code must be original work. Copying between groups is prohibited.
Plagiarism detection will be applied. Violations result in zero marks.
Credited use of documentation (Flex manual, Bison manual, LLVM docs) is
permitted and must be cited in the report.

================================================================================
CONTACT & SUPPORT
================================================================================

For questions about the project:
- Lab Instructor: Ms. Urooj Akmal
- Theory Instructor: Dr. Ahmed Rathore

Documentation references:
- Flex: https://github.com/westes/flex
- Bison: https://www.gnu.org/software/bison/
- LLVM: https://llvm.org/docs/

================================================================================
VERSION HISTORY
================================================================================

Version 1.0 - Initial project structure with all 8 modules
- Complete implementation of lexer, parser, semantic analyzer
- IR generation with TAC
- 5 optimization techniques
- LLVM IR generation support
- Comprehensive Makefile
- Test files and documentation

================================================================================
