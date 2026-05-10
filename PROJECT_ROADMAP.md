# CS-346 Compiler Project - Visual Roadmap

## 🗺️ Complete Project Roadmap

This document provides a visual overview of the entire compiler project structure and workflow.

---

## 📊 Compilation Pipeline

```
┌─────────────────────────────────────────────────────────────────┐
│                     SOURCE CODE (.c file)                        │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 1: LEXICAL ANALYSIS (Flex)                              │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  Source code characters                           │   │
│  │ Process: Pattern matching, tokenization                  │   │
│  │ Output: Token stream                                     │   │
│  │ File:   lexer/lexer.l                                    │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 2 & 3: SYNTAX ANALYSIS (Bison)                          │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  Token stream                                     │   │
│  │ Process: Grammar validation, parse tree construction     │   │
│  │ Output: Abstract Syntax Tree (AST)                       │   │
│  │ File:   parser/parser.y                                  │   │
│  │ Features: Infix/Prefix/Postfix, Exponentiation, log/exp │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 4: FIRST & FOLLOW SETS                                  │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  Grammar rules                                    │   │
│  │ Process: Set computation, LL(1) table construction       │   │
│  │ Output: FIRST sets, FOLLOW sets, Parsing table           │   │
│  │ File:   first_follow/first_follow.c                      │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 5: SEMANTIC ANALYSIS                                    │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  AST                                              │   │
│  │ Process: Type checking, scope checking                   │   │
│  │ Output: Annotated AST, Symbol table, Error messages      │   │
│  │ File:   semantic/semantic.c                              │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 6: INTERMEDIATE REPRESENTATION                          │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  Annotated AST                                    │   │
│  │ Process: TAC generation                                  │   │
│  │ Output: Three-Address Code                               │   │
│  │ File:   ir/ir_gen.c                                      │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 7: CODE OPTIMIZATION                                    │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  TAC (unoptimized)                                │   │
│  │ Process: 5 optimization techniques                       │   │
│  │         1. Constant Folding                              │   │
│  │         2. Constant Propagation                          │   │
│  │         3. Dead Code Elimination                         │   │
│  │         4. Common Subexpression Elimination              │   │
│  │         5. Strength Reduction                            │   │
│  │ Output: Optimized TAC, Performance metrics               │   │
│  │ File:   optimizer/optimizer.c                            │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│  MODULE 8: LLVM IR GENERATION                                   │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │ Input:  C source code                                    │   │
│  │ Process: LLVM compilation (unoptimized & -O3)            │   │
│  │ Output: LLVM IR (.ll files)                              │   │
│  │ Files:  llvm/test_program1.c, llvm/test_program2.c      │   │
│  └──────────────────────────────────────────────────────────┘   │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│                    EXECUTABLE / MACHINE CODE                     │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📁 Directory Structure

```
project/
│
├── 📂 lexer/                    # Module 1
│   ├── lexer.l                  # Flex specification
│   ├── lex.yy.c                 # Generated (build artifact)
│   └── lexer.exe                # Compiled executable
│
├── 📂 parser/                   # Modules 2 & 3
│   ├── parser.y                 # Bison specification
│   ├── parser.tab.c             # Generated (build artifact)
│   ├── parser.tab.h             # Generated (build artifact)
│   └── parser.exe               # Compiled executable
│
├── 📂 first_follow/             # Module 4
│   ├── first_follow.c           # C implementation
│   └── first_follow.exe         # Compiled executable
│
├── 📂 semantic/                 # Module 5
│   ├── semantic.c               # C implementation
│   └── semantic.exe             # Compiled executable
│
├── 📂 ir/                       # Module 6
│   ├── ir_gen.c                 # C implementation
│   └── ir_gen.exe               # Compiled executable
│
├── 📂 optimizer/                # Module 7
│   ├── optimizer.c              # C implementation
│   └── optimizer.exe            # Compiled executable
│
├── 📂 llvm/                     # Module 8
│   ├── test_program1.c          # Test program 1
│   ├── test_program2.c          # Test program 2
│   ├── test_program1.ll         # Unoptimized IR
│   ├── test_program1_opt.ll     # Optimized IR
│   ├── test_program2.ll         # Unoptimized IR
│   └── test_program2_opt.ll     # Optimized IR
│
├── 📄 Makefile                  # Build system
├── 📄 README.txt                # Main documentation
├── 📄 QUICKSTART.md             # Quick setup guide
├── 📄 PROJECT_SUMMARY.md        # Project overview
├── 📄 REPORT_TEMPLATE.md        # Report structure
├── 📄 SUBMISSION_CHECKLIST.md   # Pre-submission checklist
├── 📄 PROJECT_ROADMAP.md        # This file
│
├── 📄 test_input.c              # Comprehensive test file
├── 📄 input_sample.txt          # Simple test input
├── 📄 sloppy_code.c             # Unoptimized code
├── 📄 optimized_code.c          # Hand-optimized code
│
├── 🔧 build_and_test.sh         # Linux build script
└── 🔧 build_and_test.bat        # Windows build script
```

---

## 🔄 Development Workflow

```
┌─────────────────────────────────────────────────────────────────┐
│                    DEVELOPMENT PHASES                            │
└─────────────────────────────────────────────────────────────────┘

Phase 1: Setup & Prerequisites
├── Install GCC, Flex, Bison, Clang
├── Verify installations
└── Read documentation

Phase 2: Module Implementation
├── Week 1: Modules 1-2 (Lexer & Parser)
├── Week 2: Modules 3-4 (Extended Grammar & FIRST/FOLLOW)
├── Week 3: Modules 5-6 (Semantic & IR)
└── Week 4: Modules 7-8 (Optimizer & LLVM)

Phase 3: Integration & Testing
├── Integrate all modules
├── Test pipeline end-to-end
├── Fix bugs and issues
└── Capture screenshots

Phase 4: Documentation
├── Write report sections
├── Insert screenshots
├── Create tables and figures
└── Proofread and format

Phase 5: Submission
├── Final testing
├── Create ZIP package
├── Submit before deadline
└── Prepare for viva
```

---

## 🎯 Module Dependencies

```
Module 1 (Lexer)
    │
    ├──> Module 2 (Parser)
    │       │
    │       └──> Module 3 (Extended Grammar)
    │               │
    │               └──> Module 5 (Semantic)
    │                       │
    │                       └──> Module 6 (IR Gen)
    │                               │
    │                               └──> Module 7 (Optimizer)
    │
    └──> Module 4 (FIRST/FOLLOW) [Independent]

Module 8 (LLVM) [Independent - uses Clang directly]
```

---

## 📈 Grading Breakdown Visual

```
Total: 106 marks (capped at 100)

Module 1: Lexer                    ████████ 8 marks
Module 2: Parser                   ████████ 8 marks
Module 3: Extended                 ████████ 8 marks
Module 4: FIRST/FOLLOW             ████████ 8 marks
Module 5: Semantic                 ████████ 8 marks
Module 6: IR Gen                   ██████████ 10 marks
Module 7: Optimizer                ████████████████████████████████████████ 40 marks
  ├─ Task 1: Refactoring           █████ 5 marks
  ├─ Task 2: IR Printing           █████ 5 marks
  ├─ Task 3: Optimizations         ███████████████ 15 marks
  ├─ Task 4: Control Flow          ███████ 7 marks
  ├─ Task 5: Loop Opt              ████████ 8 marks
  └─ Task 6: Performance           █████ 5 marks
Module 8: LLVM                     ███████████ 11 marks
  ├─ Installation                  █████ 5 marks
  └─ Analysis                      ██████ 6 marks
Integration                        ███████ 7 marks

Code Quality: ~60%
Documentation: ~40%
```

---

## 🛠️ Build Commands Quick Reference

```bash
# Build everything
make all

# Build individual modules
make module1    # Lexer
make module2    # Parser
make module4    # FIRST/FOLLOW
make module5    # Semantic
make module6    # IR Generator
make module7    # Optimizer
make module8    # LLVM

# Test modules
make test-lexer
make test-parser
make test-first-follow
make test-semantic
make test-ir
make test-optimizer
make test-llvm

# Run all tests
make run

# Clean build artifacts
make clean

# Get help
make help
```

---

## 🧪 Testing Strategy

```
┌─────────────────────────────────────────────────────────────────┐
│                      TESTING LEVELS                              │
└─────────────────────────────────────────────────────────────────┘

Level 1: Unit Testing
├── Test each module independently
├── Verify correct output for known inputs
├── Test edge cases
└── Test error handling

Level 2: Integration Testing
├── Test module-to-module communication
├── Verify data flow through pipeline
├── Test with complex inputs
└── Verify end-to-end compilation

Level 3: Performance Testing
├── Measure optimization speedup
├── Run multiple iterations
├── Calculate average times
└── Verify improvements

Level 4: Regression Testing
├── Re-test after changes
├── Verify no functionality broken
├── Test with previous inputs
└── Compare with expected outputs
```

---

## 📝 Report Structure Visual

```
report.pdf (minimum 10 pages)
│
├── 📄 Cover Page
│   ├── University name
│   ├── Course code & name
│   ├── Project title
│   ├── Group members & roll numbers
│   └── Date
│
├── 📄 Table of Contents
│   └── With page numbers
│
├── 📄 1. Introduction
│   ├── Compiler overview
│   ├── Project scope
│   └── Technology stack
│
├── 📄 2. Module 1: Lexical Analysis
│   ├── Implementation explanation
│   ├── Token table
│   ├── Code snippets
│   └── Screenshots
│
├── 📄 3. Module 2: Syntax Analysis
│   ├── Grammar rules
│   ├── Parse trees
│   ├── Code snippets
│   └── Screenshots (3 calculators)
│
├── 📄 4. Module 3: Extended Grammar
│   ├── Extended rules
│   ├── Exponentiation
│   ├── Math functions
│   └── Screenshots
│
├── 📄 5. Module 4: FIRST & FOLLOW
│   ├── Algorithm explanation
│   ├── FIRST sets table
│   ├── FOLLOW sets table
│   ├── LL(1) table
│   └── Screenshots
│
├── 📄 6. Module 5: Semantic Analysis
│   ├── Type checking rules
│   ├── Scope management
│   ├── Symbol table
│   ├── Error examples
│   └── Screenshots
│
├── 📄 7. Module 6: IR Generation
│   ├── TAC format
│   ├── Instruction types
│   ├── Examples
│   └── Screenshots
│
├── 📄 8. Module 7: Optimization
│   ├── Each optimization explained
│   ├── Before/after IR
│   ├── Control flow analysis
│   ├── Loop optimization
│   ├── Performance table
│   └── Screenshots
│
├── 📄 9. Module 8: LLVM
│   ├── Installation verification
│   ├── Unoptimized IR (annotated)
│   ├── Optimized IR (annotated)
│   ├── Comparison
│   ├── Optimizations identified
│   └── Screenshots
│
├── 📄 10. Integration & Testing
│   ├── Pipeline integration
│   ├── Build system
│   └── Test results
│
├── 📄 11. Conclusion
│   ├── Achievements
│   ├── Challenges
│   ├── Lessons learned
│   └── Future work
│
└── 📄 12. References
    ├── Textbooks
    ├── Flex manual
    ├── Bison manual
    ├── LLVM documentation
    └── Other sources
```

---

## ⏱️ Time Estimates

```
Module 1: Lexer                    ⏱️ 4-6 hours
Module 2: Parser                   ⏱️ 6-8 hours
Module 3: Extended Grammar         ⏱️ 3-4 hours
Module 4: FIRST/FOLLOW             ⏱️ 5-7 hours
Module 5: Semantic Analysis        ⏱️ 8-10 hours
Module 6: IR Generation            ⏱️ 6-8 hours
Module 7: Optimization             ⏱️ 12-15 hours
Module 8: LLVM                     ⏱️ 4-6 hours
Integration & Testing              ⏱️ 6-8 hours
Report Writing                     ⏱️ 10-15 hours
─────────────────────────────────────────────
Total Estimated Time:              ⏱️ 64-87 hours
                                   (8-11 working days)
```

---

## 🎯 Success Criteria

```
✅ All modules compile without errors
✅ All modules produce correct output
✅ Pipeline works end-to-end
✅ Optimizations show measurable speedup
✅ LLVM IR files generated successfully
✅ Report is complete and well-formatted
✅ All screenshots captured
✅ Code is well-commented
✅ Makefile works correctly
✅ Ready for viva defense
```

---

## 🚀 Quick Start Path

```
Day 1: Setup
└── Install tools, verify installations

Day 2-3: Modules 1-2
└── Implement lexer and parser

Day 4-5: Modules 3-4
└── Extend grammar, compute FIRST/FOLLOW

Day 6-7: Modules 5-6
└── Semantic analysis and IR generation

Day 8-10: Module 7
└── Implement all optimizations

Day 11: Module 8
└── Generate and analyze LLVM IR

Day 12-13: Integration
└── Test pipeline, fix bugs

Day 14-16: Documentation
└── Write report, insert screenshots

Day 17: Final Review
└── Check everything, prepare submission

Day 18: Submit
└── Submit early, prepare for viva
```

---

## 📞 Help Resources

```
Documentation Files:
├── README.txt              → Complete guide
├── QUICKSTART.md           → 5-minute setup
├── PROJECT_SUMMARY.md      → Overview
├── REPORT_TEMPLATE.md      → Report structure
├── SUBMISSION_CHECKLIST.md → Pre-submission checks
└── PROJECT_ROADMAP.md      → This file

Online Resources:
├── Flex Manual             → https://github.com/westes/flex
├── Bison Manual            → https://www.gnu.org/software/bison/
├── LLVM Documentation      → https://llvm.org/docs/
└── Compiler Textbook       → Aho, Lam, Sethi, Ullman (Dragon Book)

Instructors:
├── Lab: Ms. Urooj Akmal
└── Theory: Dr. Ahmed Rathore
```

---

## 🎓 Final Notes

**Remember:**
- Start early, don't procrastinate
- Test frequently, catch bugs early
- Document as you go
- Ask questions when stuck
- Prepare thoroughly for viva
- Be proud of your work!

**Good luck with your compiler project! 🚀**

---

*Project Roadmap Version 1.0*  
*CS-346 Compiler Construction - NUST SEECS*
