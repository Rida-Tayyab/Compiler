# CS-346 Compiler Project - Quick Start Guide

## 🚀 Get Started in 5 Minutes

### Step 1: Verify Prerequisites

**Windows:**
```cmd
gcc --version
win_flex --version
win_bison --version
clang --version
```

**Linux:**
```bash
gcc --version
flex --version
bison --version
clang --version
```

If any command fails, install the missing tool (see README.txt).

---

### Step 2: Build Everything

```bash
make all
```

This builds modules 1, 4, 5, 6, and 7.

---

### Step 3: Test Each Module

#### Module 1: Lexical Analyzer
```bash
make test-lexer
```
**Expected:** Token table with keywords, identifiers, operators

#### Module 4: FIRST & FOLLOW Sets
```bash
make test-first-follow
```
**Expected:** FIRST and FOLLOW sets for grammar

#### Module 5: Semantic Analyzer
```bash
make test-semantic
```
**Expected:** Symbol table with scope levels

#### Module 6: IR Generator
```bash
make test-ir
```
**Expected:** Three-Address Code (TAC) listings

#### Module 7: Optimizer
```bash
make test-optimizer
```
**Expected:** Before/after IR, performance comparison

#### Module 8: LLVM IR
```bash
make module8
make test-llvm
```
**Expected:** .ll files in llvm/ directory

---

### Step 4: View Results

**Lexer output:**
```bash
./lexer/lexer < test_input.c
```

**Optimizer output:**
```bash
./optimizer/optimizer sloppy_code.c
```

**LLVM IR files:**
```bash
cat llvm/test_program1.ll
cat llvm/test_program1_opt.ll
```

---

## 📊 What Each Module Does

| Module | Input | Output |
|--------|-------|--------|
| 1. Lexer | Source code | Token stream |
| 2. Parser | Tokens | Parse tree |
| 3. Extended | Expressions | Evaluated results |
| 4. FIRST/FOLLOW | Grammar | Parsing table |
| 5. Semantic | AST | Symbol table + errors |
| 6. IR Gen | AST | Three-Address Code |
| 7. Optimizer | TAC | Optimized TAC |
| 8. LLVM | C code | LLVM IR (.ll files) |

---

## 🔧 Common Commands

**Build specific module:**
```bash
make module1    # Lexer
make module4    # FIRST/FOLLOW
make module5    # Semantic
make module6    # IR Generator
make module7    # Optimizer
make module8    # LLVM
```

**Clean everything:**
```bash
make clean
```

**Run all tests:**
```bash
make run
```

**Get help:**
```bash
make help
```

---

## 📝 Quick Testing

**Test with your own C file:**
```bash
# Lexer
./lexer/lexer < your_file.c

# Optimizer
./optimizer/optimizer your_file.c

# LLVM IR
clang -S -emit-llvm your_file.c -o output.ll
clang -S -emit-llvm -O3 your_file.c -o output_opt.ll
```

---

## 🐛 Troubleshooting

**Problem:** `make: command not found`
- **Windows:** Install MinGW or use Git Bash
- **Linux:** `sudo apt-get install build-essential`

**Problem:** `flex: command not found`
- **Windows:** Download win_flex from GnuWin32
- **Linux:** `sudo apt-get install flex`

**Problem:** `bison: command not found`
- **Windows:** Download win_bison from GnuWin32
- **Linux:** `sudo apt-get install bison`

**Problem:** `clang: command not found`
- **Windows:** Download from https://releases.llvm.org/
- **Linux:** `sudo apt-get install clang llvm`

**Problem:** Compilation errors
- Check that all files are in correct directories
- Verify Makefile paths match your system
- Try `make clean` then `make all`

---

## 📚 Next Steps

1. ✅ Build all modules
2. ✅ Run tests and verify output
3. ✅ Take screenshots for report
4. ✅ Analyze optimization results
5. ✅ Compare LLVM IR files
6. ✅ Write report using REPORT_TEMPLATE.md
7. ✅ Prepare for viva

---

## 🎯 Grading Checklist

- [ ] All modules compile without errors
- [ ] Lexer produces correct token table
- [ ] Parser handles all expression types
- [ ] FIRST/FOLLOW sets are correct
- [ ] Semantic analyzer detects errors
- [ ] IR generator produces valid TAC
- [ ] Optimizer implements 5 techniques
- [ ] Performance comparison shows speedup
- [ ] LLVM IR files generated
- [ ] Report includes all sections
- [ ] Screenshots included
- [ ] Code is well-commented
- [ ] Makefile works correctly

---

## 💡 Tips for Success

1. **Test incrementally** - Don't wait until the end
2. **Take screenshots** - Capture output as you go
3. **Comment your code** - Explain your decisions
4. **Measure performance** - Run optimizer multiple times
5. **Compare IR** - Annotate LLVM optimizations
6. **Document challenges** - Note what you learned
7. **Cite sources** - Reference manuals and docs

---

## 📞 Need Help?

- Check README.txt for detailed documentation
- Review REPORT_TEMPLATE.md for report structure
- Consult Flex/Bison/LLVM documentation
- Ask instructors during lab sessions

---

**Good luck with your project! 🎓**
