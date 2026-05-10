# CS-346 Compiler Project - Submission Checklist

## 📦 Pre-Submission Checklist

Use this checklist to ensure your project is complete before submission.

---

## ✅ Code Files

### Module 1: Lexical Analysis
- [ ] `lexer/lexer.l` exists and compiles
- [ ] Recognizes all required token types
- [ ] Handles comments correctly
- [ ] Computes hash values
- [ ] Tracks line numbers
- [ ] Tested with sample input

### Module 2 & 3: Syntax Analysis
- [ ] `parser/parser.y` exists and compiles
- [ ] Implements expression grammar
- [ ] Handles operator precedence
- [ ] Supports exponentiation (right-associative)
- [ ] Includes mathematical functions (log, exp)
- [ ] Tested with multiple expressions

### Module 4: FIRST & FOLLOW
- [ ] `first_follow/first_follow.c` exists and compiles
- [ ] Computes FIRST sets correctly
- [ ] Computes FOLLOW sets correctly
- [ ] Builds LL(1) parsing table
- [ ] Verifies LL(1) compatibility
- [ ] Output matches expected sets

### Module 5: Semantic Analysis
- [ ] `semantic/semantic.c` exists and compiles
- [ ] Implements type checking
- [ ] Implements scope checking
- [ ] Maintains symbol table
- [ ] Detects undeclared variables
- [ ] Detects redeclarations
- [ ] Detects type mismatches
- [ ] Tested with error cases

### Module 6: IR Generation
- [ ] `ir/ir_gen.c` exists and compiles
- [ ] Generates Three-Address Code
- [ ] Supports all TAC forms
- [ ] Generates temporary variables
- [ ] Generates labels
- [ ] Handles expressions, control flow, functions
- [ ] Output is readable and correct

### Module 7: Code Optimization
- [ ] `optimizer/optimizer.c` exists and compiles
- [ ] Implements constant folding
- [ ] Implements constant propagation
- [ ] Implements dead code elimination
- [ ] Implements common subexpression elimination
- [ ] Implements strength reduction
- [ ] Prints IR before optimization
- [ ] Prints IR after each optimization
- [ ] Detects unreachable code
- [ ] Includes loop optimization
- [ ] Performance comparison implemented
- [ ] Runs 5 iterations for timing
- [ ] Calculates speedup ratio
- [ ] Tested with sloppy_code.c

### Module 8: LLVM IR
- [ ] `llvm/test_program1.c` exists
- [ ] `llvm/test_program2.c` exists
- [ ] Unoptimized IR generated (.ll files)
- [ ] Optimized IR generated (_opt.ll files)
- [ ] IR files are annotated
- [ ] Optimizations identified and documented

---

## ✅ Build System

- [ ] `Makefile` exists
- [ ] `make all` builds all modules
- [ ] `make module1` through `make module8` work
- [ ] `make test-*` targets work
- [ ] `make clean` removes all build artifacts
- [ ] `make help` displays usage information
- [ ] Works on target platform (Windows/Linux)

---

## ✅ Documentation

### README.txt
- [ ] Exists and is complete
- [ ] Includes project overview
- [ ] Lists prerequisites
- [ ] Provides build instructions
- [ ] Provides run instructions
- [ ] Includes module descriptions
- [ ] Includes troubleshooting section
- [ ] Includes contact information

### Additional Documentation
- [ ] QUICKSTART.md exists
- [ ] PROJECT_SUMMARY.md exists
- [ ] REPORT_TEMPLATE.md exists
- [ ] All documentation is up-to-date

---

## ✅ Test Files

- [ ] `test_input.c` exists
- [ ] `input_sample.txt` exists
- [ ] `sloppy_code.c` exists
- [ ] `optimized_code.c` exists
- [ ] Test files cover all language features
- [ ] Test files demonstrate optimizations

---

## ✅ Report (PDF)

### Structure
- [ ] Cover page with all required information
- [ ] Table of contents with page numbers
- [ ] Introduction section
- [ ] Module 1-8 sections
- [ ] Conclusion section
- [ ] References section
- [ ] Minimum 10 pages
- [ ] Font: Arial or Times New Roman 11-12pt
- [ ] Page numbers on all pages except cover

### Module 1 Section
- [ ] Explanation of implementation
- [ ] Token table included
- [ ] Code snippets included
- [ ] Screenshot of token output
- [ ] Sample input shown

### Module 2 Section
- [ ] Grammar rules explained
- [ ] Precedence/associativity discussed
- [ ] Parse tree examples
- [ ] Screenshots of all three calculators
- [ ] At least 2 sample expressions per type

### Module 3 Section
- [ ] Extended grammar listed
- [ ] Exponentiation explained
- [ ] Mathematical functions demonstrated
- [ ] Screenshot of log/exp evaluation

### Module 4 Section
- [ ] FIRST sets table
- [ ] FOLLOW sets table
- [ ] LL(1) parsing table
- [ ] Screenshot of program output
- [ ] Correctness verification

### Module 5 Section
- [ ] Symbol table design explained
- [ ] Type checking rules documented
- [ ] Scope management described
- [ ] Error examples shown
- [ ] Screenshot of semantic analysis

### Module 6 Section
- [ ] TAC format described
- [ ] All instruction types explained
- [ ] Sample TAC output included
- [ ] Screenshot of IR generation
- [ ] Multiple examples shown

### Module 7 Section
- [ ] All 5 optimizations explained
- [ ] Before/after IR for each technique
- [ ] Control flow analysis described
- [ ] Loop optimization explained
- [ ] Performance comparison table
- [ ] Table includes 5 runs
- [ ] Speedup ratio calculated
- [ ] Screenshots of optimizer output

### Module 8 Section
- [ ] Installation screenshot (clang --version)
- [ ] Unoptimized IR excerpts
- [ ] Optimized IR excerpts
- [ ] Side-by-side comparison
- [ ] At least 3 optimizations identified
- [ ] Key instructions explained (alloca, load, store, ret, add, call)
- [ ] Annotations on IR code

### Formatting
- [ ] All tables have captions
- [ ] All figures have captions
- [ ] Code snippets are syntax-highlighted or monospace
- [ ] Screenshots are clear and readable
- [ ] Before/after listings are clearly labeled
- [ ] Consistent formatting throughout

---

## ✅ Integration & Testing

- [ ] All modules compile without errors
- [ ] All modules compile without warnings
- [ ] Lexer integrates with parser
- [ ] Parser integrates with semantic analyzer
- [ ] Semantic analyzer integrates with IR generator
- [ ] IR generator integrates with optimizer
- [ ] All modules tested individually
- [ ] Pipeline tested end-to-end
- [ ] Error handling works correctly
- [ ] Edge cases handled

---

## ✅ Code Quality

- [ ] Code is well-commented
- [ ] Functions have descriptive names
- [ ] Variables have meaningful names
- [ ] No magic numbers (use constants)
- [ ] Consistent indentation
- [ ] Consistent naming convention
- [ ] No compiler warnings
- [ ] No memory leaks (if applicable)
- [ ] Error messages are descriptive
- [ ] Code follows best practices

---

## ✅ Screenshots

### Required Screenshots
- [ ] Lexer token table output
- [ ] Postfix calculator output
- [ ] Prefix calculator output
- [ ] Infix calculator output
- [ ] Extended grammar evaluation (log/exp)
- [ ] FIRST sets output
- [ ] FOLLOW sets output
- [ ] LL(1) parsing table
- [ ] Symbol table
- [ ] Type error example
- [ ] Scope error example
- [ ] TAC output (multiple examples)
- [ ] Optimizer: before optimization
- [ ] Optimizer: after constant folding
- [ ] Optimizer: after constant propagation
- [ ] Optimizer: after dead code elimination
- [ ] Optimizer: after CSE
- [ ] Optimizer: after strength reduction
- [ ] Performance comparison table
- [ ] clang --version output
- [ ] Unoptimized LLVM IR
- [ ] Optimized LLVM IR

### Screenshot Quality
- [ ] All screenshots are clear
- [ ] Text is readable
- [ ] No unnecessary content
- [ ] Properly cropped
- [ ] Labeled in report

---

## ✅ Submission Package

### ZIP Archive Contents
- [ ] All source files (.l, .y, .c, .h)
- [ ] Makefile
- [ ] README.txt
- [ ] Test files
- [ ] report.pdf
- [ ] No compiled binaries (.exe, .o, .out)
- [ ] No generated files (lex.yy.c, parser.tab.c)
- [ ] No IDE-specific files
- [ ] Proper directory structure maintained

### File Organization
```
project.zip
├── lexer/
│   └── lexer.l
├── parser/
│   └── parser.y
├── first_follow/
│   └── first_follow.c
├── semantic/
│   └── semantic.c
├── ir/
│   └── ir_gen.c
├── optimizer/
│   └── optimizer.c
├── llvm/
│   ├── test_program1.c
│   └── test_program2.c
├── Makefile
├── README.txt
├── test_input.c
├── sloppy_code.c
├── optimized_code.c
└── report.pdf
```

---

## ✅ Viva Preparation

- [ ] Understand every line of code
- [ ] Can explain lexer patterns
- [ ] Can explain grammar rules
- [ ] Can explain FIRST/FOLLOW algorithm
- [ ] Can explain type checking rules
- [ ] Can explain TAC generation
- [ ] Can explain each optimization technique
- [ ] Can explain LLVM optimizations
- [ ] Can demonstrate running the compiler
- [ ] Can answer "why" questions about design decisions
- [ ] Prepared to modify code if asked
- [ ] Prepared to add features if asked

---

## ✅ Final Checks

- [ ] Project compiles on clean system
- [ ] All paths are relative (no absolute paths)
- [ ] No hardcoded usernames or system-specific paths
- [ ] Works on both Windows and Linux (if applicable)
- [ ] README instructions are accurate
- [ ] Report matches actual implementation
- [ ] All group members listed correctly
- [ ] Submission deadline noted
- [ ] File size is reasonable (< 50MB)
- [ ] ZIP file extracts correctly

---

## ✅ Academic Integrity

- [ ] All code is original work
- [ ] No code copied from other groups
- [ ] All references cited in report
- [ ] Flex/Bison/LLVM documentation cited
- [ ] No plagiarism in report text
- [ ] Understand consequences of violations

---

## 📊 Grading Self-Assessment

Rate your completion for each module (0-100%):

| Module | Completion | Notes |
|--------|-----------|-------|
| Module 1: Lexer | ___% | |
| Module 2: Parser | ___% | |
| Module 3: Extended | ___% | |
| Module 4: FIRST/FOLLOW | ___% | |
| Module 5: Semantic | ___% | |
| Module 6: IR Gen | ___% | |
| Module 7: Optimizer | ___% | |
| Module 8: LLVM | ___% | |
| Integration | ___% | |
| Report | ___% | |

**Overall Completion:** ____%

---

## 🎯 Pre-Submission Actions

1. [ ] Run `make clean` then `make all`
2. [ ] Test all modules one final time
3. [ ] Verify all screenshots are in report
4. [ ] Proofread report for typos
5. [ ] Check report page count (minimum 10)
6. [ ] Verify ZIP file contents
7. [ ] Test ZIP extraction
8. [ ] Submit before deadline
9. [ ] Keep backup copy
10. [ ] Confirm submission received

---

## 📅 Timeline Suggestion

**2 weeks before deadline:**
- [ ] All modules implemented
- [ ] All modules tested
- [ ] Screenshots captured

**1 week before deadline:**
- [ ] Report first draft complete
- [ ] All sections written
- [ ] All screenshots inserted

**3 days before deadline:**
- [ ] Report reviewed and revised
- [ ] Code cleaned and commented
- [ ] Integration tested

**1 day before deadline:**
- [ ] Final testing
- [ ] ZIP package created
- [ ] Submission ready

**Deadline day:**
- [ ] Final checks
- [ ] Submit early (don't wait until last minute)
- [ ] Verify submission

---

## ✉️ Submission Confirmation

After submission:
- [ ] Received confirmation email/receipt
- [ ] Verified file uploaded correctly
- [ ] Noted submission timestamp
- [ ] Kept backup copy
- [ ] Prepared for viva

---

## 🎓 Good Luck!

**Remember:**
- Start early
- Test frequently
- Document thoroughly
- Ask questions when stuck
- Prepare for viva
- Be proud of your work!

---

**Checklist Version:** 1.0  
**Last Updated:** [Date]
