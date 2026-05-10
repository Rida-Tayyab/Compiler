// CS-346 Compiler Project - Comprehensive Test Input
// Tests all compiler phases and language features

#include <stdio.h>
#include <math.h>

// Global variables for testing scope
int global_x = 100;
float global_y = 3.14;

// Function declarations
int add(int a, int b);
float calculate(float x, float y);

int main() {
    // Variable declarations (Module 5: Semantic Analysis)
    int x = 10;
    float y = 2.5;
    double z = 1.414;
    char c = 'A';
    
    // Arithmetic expressions (Module 1: Lexical Analysis)
    int sum = x + 5;
    int diff = x - 3;
    int prod = x * 2;
    int quot = x / 2;
    
    // Relational and logical operators (Module 1: Lexical Analysis)
    if (x == 10 && y > 2.0) {
        sum = sum + 1;
    }
    
    if (x != 0 || y <= 5.0) {
        diff = diff - 1;
    }
    
    // Nested scopes (Module 5: Semantic Analysis)
    {
        int local_var = 20;
        float local_y = 1.5;
        
        {
            int inner_var = 30;
            char inner_c = 'B';
            local_var = local_var + inner_var;
        }
        
        x = x + local_var;
    }
    
    // Optimization opportunities (Module 7: Code Optimization)
    
    // 1. Constant folding
    int const1 = 5 + 10 * 2;        // Should fold to 25
    int const2 = (8 + 2) * 3;       // Should fold to 30
    
    // 2. Constant propagation
    int multiplier = 100;
    int result1 = multiplier * 2;    // Can use multiplier value
    int result2 = multiplier + 50;   // Can use multiplier value
    
    // 3. Strength reduction
    int shifted1 = x * 2;            // Can become x << 1
    int shifted2 = x * 4;            // Can become x << 2
    int shifted3 = x / 2;            // Can become x >> 1
    
    // 4. Common subexpression elimination
    int expr1 = x + y * 2;
    int expr2 = x + y * 2;           // Same as expr1
    int expr3 = x + y * 2;           // Same as expr1
    
    // Function calls (Module 6: IR Generation)
    int func_result = add(x, 5);
    float calc_result = calculate(y, 3.0);
    
    // Control flow (Module 6: IR Generation)
    while (x < 50) {
        x = x + 10;
        if (x == 30) {
            break;
            int unreachable = 999;   // Dead code after break
        }
    }
    
    // More dead code (Module 7: Optimization)
    return 0;
    int dead_var = 777;              // Unreachable after return
    x = dead_var + 10;               // Unreachable after return
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

float calculate(float x, float y) {
    // Mathematical operations for extended grammar
    float result = x + y;
    
    // Constant folding opportunity
    float const_expr = 2.0 + 3.0 * 4.0;  // Should fold to 14.0
    
    return result + const_expr;
}

// Function with more optimization opportunities
int optimization_test() {
    int a = 2 + 3 * 4;               // Constant folding: 14
    int b = 100;                     // Constant propagation
    int c = b * 2;                   // Use b's value: 200
    int d = b + 50;                  // Use b's value: 150
    
    // Strength reduction
    int e = a * 2;                   // a << 1
    int f = a * 8;                   // a << 3
    int g = a / 4;                   // a >> 2
    
    return a + c;
    
    // Dead code below
    int unused1 = 999;
    int unused2 = unused1 + e;
    return unused2;
}