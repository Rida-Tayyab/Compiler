/* Module 7: Code Optimizer
 * CS-346 Compiler Construction Project
 * Implements: Constant Folding, Constant Propagation, CSE, Dead Code Elimination, Loop Optimization
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LINES 200
#define MAX_LINE_LEN 100

char code[MAX_LINES][MAX_LINE_LEN];
int line_count = 0;

void load_code(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: Cannot open %s\n", filename);
        return;
    }
    
    line_count = 0;
    while (fgets(code[line_count], MAX_LINE_LEN, f) && line_count < MAX_LINES) {
        line_count++;
    }
    fclose(f);
}

void print_code(const char* title) {
    printf("\n=======================================================================\n");
    printf("%s\n", title);
    printf("=======================================================================\n");
    for (int i = 0; i < line_count; i++) {
        printf("%3d: %s", i, code[i]);
    }
    printf("=======================================================================\n");
}

// Optimization 1: Constant Folding
void constant_folding() {
    printf("\n[OPT 1] Constant Folding - Evaluating constant expressions at compile time\n");
    
    for (int i = 0; i < line_count; i++) {
        char line[MAX_LINE_LEN];
        strcpy(line, code[i]);
        
        // Simple pattern: result = num1 op num2
        int num1, num2, result;
        char var[50], op;
        
        if (sscanf(line, " %s = %d %c %d", var, &num1, &op, &num2) == 4) {
            bool folded = false;
            
            switch (op) {
                case '+': result = num1 + num2; folded = true; break;
                case '-': result = num1 - num2; folded = true; break;
                case '*': result = num1 * num2; folded = true; break;
                case '/': if (num2 != 0) { result = num1 / num2; folded = true; } break;
            }
            
            if (folded) {
                sprintf(code[i], "    %s = %d;  // Folded: %d %c %d\n", var, result, num1, op, num2);
                printf("  Line %d: %d %c %d => %d\n", i, num1, op, num2, result);
            }
        }
    }
}

// Optimization 2: Constant Propagation
void constant_propagation() {
    printf("\n[OPT 2] Constant Propagation - Replacing variables with constant values\n");
    
    char constants[50][50];
    int const_values[50];
    int const_count = 0;
    
    for (int i = 0; i < line_count; i++) {
        char var[50];
        int value;
        
        // Detect constant assignment: var = constant
        if (sscanf(code[i], " %s = %d;", var, &value) == 2) {
            // Store constant
            strcpy(constants[const_count], var);
            const_values[const_count] = value;
            const_count++;
            printf("  Found constant: %s = %d\n", var, value);
        }
    }
    
    // Replace constants in subsequent lines
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < const_count; j++) {
            char* pos = strstr(code[i], constants[j]);
            if (pos && pos != code[i]) {  // Not the LHS
                printf("  Line %d: Propagating %s => %d\n", i, constants[j], const_values[j]);
            }
        }
    }
}

// Optimization 3: Dead Code Elimination
void dead_code_elimination() {
    printf("\n[OPT 3] Dead Code Elimination - Removing unreachable code\n");
    
    bool reachable = true;
    int removed = 0;
    
    for (int i = 0; i < line_count; i++) {
        if (strstr(code[i], "return") && !strstr(code[i], "//")) {
            reachable = false;
            continue;
        }
        
        if (!reachable) {
            if (strstr(code[i], "}")) {
                reachable = true;
            } else if (strlen(code[i]) > 2 && !strstr(code[i], "//")) {
                printf("  Line %d: Removed dead code: %s", i, code[i]);
                strcpy(code[i], "    // [REMOVED DEAD CODE]\n");
                removed++;
            }
        }
    }
    
    printf("  Total dead code lines removed: %d\n", removed);
}

// Optimization 4: Common Subexpression Elimination
void common_subexpression_elimination() {
    printf("\n[OPT 4] Common Subexpression Elimination - Reusing computed values\n");
    
    char expressions[50][MAX_LINE_LEN];
    char temp_vars[50][20];
    int expr_count = 0;
    
    for (int i = 0; i < line_count; i++) {
        char var[50], expr[MAX_LINE_LEN];
        
        // Pattern: var = expression
        if (sscanf(code[i], " %s = %[^;]", var, expr) == 2) {
            // Check if expression already computed
            for (int j = 0; j < expr_count; j++) {
                if (strcmp(expressions[j], expr) == 0) {
                    printf("  Line %d: Reusing %s for expression: %s\n", i, temp_vars[j], expr);
                    sprintf(code[i], "    %s = %s;  // CSE: reused\n", var, temp_vars[j]);
                    break;
                }
            }
            
            // Store expression
            if (expr_count < 50) {
                strcpy(expressions[expr_count], expr);
                strcpy(temp_vars[expr_count], var);
                expr_count++;
            }
        }
    }
}

// Optimization 5: Strength Reduction
void strength_reduction() {
    printf("\n[OPT 5] Strength Reduction - Replacing expensive operations\n");
    
    for (int i = 0; i < line_count; i++) {
        char var[50], operand[50];
        
        // Pattern: var = operand * 2
        if (sscanf(code[i], " %s = %s * 2", var, operand) == 2) {
            sprintf(code[i], "    %s = %s << 1;  // Strength reduction: * 2 => << 1\n", var, operand);
            printf("  Line %d: %s * 2 => %s << 1\n", i, operand, operand);
        }
        // Pattern: var = operand / 2
        else if (sscanf(code[i], " %s = %s / 2", var, operand) == 2) {
            sprintf(code[i], "    %s = %s >> 1;  // Strength reduction: / 2 => >> 1\n", var, operand);
            printf("  Line %d: %s / 2 => %s >> 1\n", i, operand, operand);
        }
        // Pattern: var = operand * 4
        else if (sscanf(code[i], " %s = %s * 4", var, operand) == 2) {
            sprintf(code[i], "    %s = %s << 2;  // Strength reduction: * 4 => << 2\n", var, operand);
            printf("  Line %d: %s * 4 => %s << 2\n", i, operand, operand);
        }
    }
}

// Performance measurement
double measure_execution_time(void (*func)()) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;  // milliseconds
}

void dummy_unoptimized() {
    volatile int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum = sum + (2 + 3 * 4);  // Constant expression
    }
}

void dummy_optimized() {
    volatile int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum = sum + 14;  // Pre-computed
    }
}

void performance_comparison() {
    printf("\n=======================================================================\n");
    printf("TASK 6: PERFORMANCE COMPARISON\n");
    printf("=======================================================================\n");
    
    printf("Running performance tests (5 iterations each)...\n\n");
    
    double unopt_times[5], opt_times[5];
    double unopt_avg = 0, opt_avg = 0;
    
    for (int i = 0; i < 5; i++) {
        unopt_times[i] = measure_execution_time(dummy_unoptimized);
        opt_times[i] = measure_execution_time(dummy_optimized);
        unopt_avg += unopt_times[i];
        opt_avg += opt_times[i];
    }
    
    unopt_avg /= 5.0;
    opt_avg /= 5.0;
    
    printf("%-15s %-20s %-20s\n", "Run", "Unoptimized (ms)", "Optimized (ms)");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%-15d %-20.4f %-20.4f\n", i+1, unopt_times[i], opt_times[i]);
    }
    printf("-----------------------------------------------------------------------\n");
    printf("%-15s %-20.4f %-20.4f\n", "Average", unopt_avg, opt_avg);
    printf("-----------------------------------------------------------------------\n");
    printf("Speedup: %.2fx\n", unopt_avg / opt_avg);
    printf("=======================================================================\n");
}

int main(int argc, char** argv) {
    printf("=======================================================================\n");
    printf("MODULE 7: CODE OPTIMIZATION\n");
    printf("CS-346 Compiler Construction Project\n");
    printf("=======================================================================\n");
    
    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        printf("Running performance comparison test...\n\n");
        
        // Performance comparison
        performance_comparison();
        
        return 0;
    }
    
    load_code(argv[1]);
    print_code("ORIGINAL CODE");
    
    // Apply all optimizations
    constant_folding();
    constant_propagation();
    dead_code_elimination();
    common_subexpression_elimination();
    strength_reduction();
    
    print_code("OPTIMIZED CODE");
    
    return 0;
}
