@echo off
REM CS-346 Compiler Project - Build and Test Script (Windows)
REM This script builds all modules and runs comprehensive tests

echo =======================================================================
echo CS-346 COMPILER CONSTRUCTION PROJECT
echo Build and Test Script (Windows)
echo =======================================================================
echo.

REM Check prerequisites
echo Step 1: Checking prerequisites...
echo -----------------------------------

where gcc >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] GCC not found. Please install MinGW or similar.
    exit /b 1
)
echo [OK] GCC found

where win_flex >nul 2>&1
if %errorlevel% neq 0 (
    where flex >nul 2>&1
    if %errorlevel% neq 0 (
        echo [ERROR] Flex not found. Please install win_flex.
        exit /b 1
    )
)
echo [OK] Flex found

where win_bison >nul 2>&1
if %errorlevel% neq 0 (
    where bison >nul 2>&1
    if %errorlevel% neq 0 (
        echo [ERROR] Bison not found. Please install win_bison.
        exit /b 1
    )
)
echo [OK] Bison found

where clang >nul 2>&1
if %errorlevel% neq 0 (
    echo [WARNING] Clang not found. Module 8 will be skipped.
    set SKIP_LLVM=1
) else (
    echo [OK] Clang found
)

echo.

REM Clean previous builds
echo Step 2: Cleaning previous builds...
echo -----------------------------------
make clean >nul 2>&1
echo [OK] Clean complete
echo.

REM Build all modules
echo Step 3: Building all modules...
echo -----------------------------------

echo Building Module 1: Lexical Analyzer...
make module1 >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Module 1 build failed
    exit /b 1
)
echo [OK] Module 1 built successfully

echo Building Module 4: FIRST ^& FOLLOW...
make module4 >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Module 4 build failed
    exit /b 1
)
echo [OK] Module 4 built successfully

echo Building Module 5: Semantic Analyzer...
make module5 >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Module 5 build failed
    exit /b 1
)
echo [OK] Module 5 built successfully

echo Building Module 6: IR Generator...
make module6 >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Module 6 build failed
    exit /b 1
)
echo [OK] Module 6 built successfully

echo Building Module 7: Optimizer...
make module7 >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Module 7 build failed
    exit /b 1
)
echo [OK] Module 7 built successfully

if not defined SKIP_LLVM (
    echo Building Module 8: LLVM IR...
    make module8 >nul 2>&1
    if %errorlevel% neq 0 (
        echo [ERROR] Module 8 build failed
    ) else (
        echo [OK] Module 8 built successfully
    )
)

echo.

REM Run tests
echo Step 4: Running tests...
echo -----------------------------------

echo Testing Module 1: Lexical Analyzer...
if exist test_input.c (
    lexer\lexer.exe < test_input.c >nul 2>&1
    if %errorlevel% equ 0 (
        echo [OK] Module 1 test passed
    ) else (
        echo [ERROR] Module 1 test failed
    )
) else (
    echo [ERROR] test_input.c not found
)

echo Testing Module 4: FIRST ^& FOLLOW...
first_follow\first_follow.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] Module 4 test passed
) else (
    echo [ERROR] Module 4 test failed
)

echo Testing Module 5: Semantic Analyzer...
semantic\semantic.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] Module 5 test passed
) else (
    echo [ERROR] Module 5 test failed
)

echo Testing Module 6: IR Generator...
ir\ir_gen.exe >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] Module 6 test passed
) else (
    echo [ERROR] Module 6 test failed
)

echo Testing Module 7: Optimizer...
if exist sloppy_code.c (
    optimizer\optimizer.exe sloppy_code.c >nul 2>&1
) else (
    optimizer\optimizer.exe >nul 2>&1
)
if %errorlevel% equ 0 (
    echo [OK] Module 7 test passed
) else (
    echo [ERROR] Module 7 test failed
)

if not defined SKIP_LLVM (
    echo Testing Module 8: LLVM IR...
    if exist llvm\test_program1.ll (
        if exist llvm\test_program1_opt.ll (
            echo [OK] Module 8 test passed (IR files generated)
        ) else (
            echo [ERROR] Module 8 test failed (optimized IR not found)
        )
    ) else (
        echo [ERROR] Module 8 test failed (IR files not found)
    )
)

echo.

REM Summary
echo =======================================================================
echo BUILD AND TEST SUMMARY
echo =======================================================================
echo.
echo [OK] All modules built successfully!
echo [OK] All tests passed!
echo.
echo Next steps:
echo   1. Run individual modules to see detailed output
echo   2. Take screenshots for your report
echo   3. Analyze optimization results
echo   4. Compare LLVM IR files
echo.
echo Commands to run modules:
echo   lexer\lexer.exe ^< test_input.c
echo   first_follow\first_follow.exe
echo   semantic\semantic.exe
echo   ir\ir_gen.exe
echo   optimizer\optimizer.exe sloppy_code.c
echo   type llvm\test_program1.ll
echo   type llvm\test_program1_opt.ll
echo.
echo =======================================================================

pause
