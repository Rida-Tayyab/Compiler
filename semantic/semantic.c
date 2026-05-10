/* Module 5: Semantic Analyzer - Type and Scope Checking
 * CS-346 Compiler Construction Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SYMBOLS 100
#define MAX_SCOPES 20
#define MAX_NAME_LEN 50

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    char name[MAX_NAME_LEN];
    DataType type;
    int scope_level;
    int line_declared;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

typedef struct {
    int scope_stack[MAX_SCOPES];
    int top;
    int current_scope;
} ScopeManager;

SymbolTable symbol_table;
ScopeManager scope_mgr;
int error_count = 0;

const char* type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}

DataType string_to_type(const char* str) {
    if (strcmp(str, "int") == 0) return TYPE_INT;
    if (strcmp(str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(str, "double") == 0) return TYPE_DOUBLE;
    if (strcmp(str, "char") == 0) return TYPE_CHAR;
    if (strcmp(str, "void") == 0) return TYPE_VOID;
    return TYPE_UNKNOWN;
}

void init_semantic_analyzer() {
    symbol_table.count = 0;
    scope_mgr.top = -1;
    scope_mgr.current_scope = 0;
    error_count = 0;
}

void enter_scope() {
    scope_mgr.top++;
    scope_mgr.current_scope++;
    scope_mgr.scope_stack[scope_mgr.top] = scope_mgr.current_scope;
    printf("[SCOPE] Entered scope level %d\n", scope_mgr.current_scope);
}

void exit_scope() {
    if (scope_mgr.top >= 0) {
        printf("[SCOPE] Exited scope level %d\n", scope_mgr.current_scope);
        scope_mgr.top--;
        if (scope_mgr.top >= 0) {
            scope_mgr.current_scope = scope_mgr.scope_stack[scope_mgr.top];
        } else {
            scope_mgr.current_scope = 0;
        }
    }
}

Symbol* lookup_symbol(const char* name) {
    // Search from current scope backwards to global
    for (int i = symbol_table.count - 1; i >= 0; i--) {
        if (strcmp(symbol_table.symbols[i].name, name) == 0) {
            if (symbol_table.symbols[i].scope_level <= scope_mgr.current_scope) {
                return &symbol_table.symbols[i];
            }
        }
    }
    return NULL;
}

Symbol* lookup_in_current_scope(const char* name) {
    for (int i = symbol_table.count - 1; i >= 0; i--) {
        if (strcmp(symbol_table.symbols[i].name, name) == 0 &&
            symbol_table.symbols[i].scope_level == scope_mgr.current_scope) {
            return &symbol_table.symbols[i];
        }
    }
    return NULL;
}

bool declare_symbol(const char* name, DataType type, int line) {
    // Check if already declared in current scope
    if (lookup_in_current_scope(name) != NULL) {
        printf("[ERROR] Line %d: Variable '%s' already declared in current scope\n", line, name);
        error_count++;
        return false;
    }
    
    if (symbol_table.count >= MAX_SYMBOLS) {
        printf("[ERROR] Symbol table overflow\n");
        error_count++;
        return false;
    }
    
    Symbol* sym = &symbol_table.symbols[symbol_table.count];
    strcpy(sym->name, name);
    sym->type = type;
    sym->scope_level = scope_mgr.current_scope;
    sym->line_declared = line;
    symbol_table.count++;
    
    printf("[DECLARE] %s %s at scope %d (line %d)\n", 
           type_to_string(type), name, scope_mgr.current_scope, line);
    
    return true;
}

bool check_variable_declared(const char* name, int line) {
    Symbol* sym = lookup_symbol(name);
    if (sym == NULL) {
        printf("[ERROR] Line %d: Variable '%s' used before declaration\n", line, name);
        error_count++;
        return false;
    }
    return true;
}

DataType get_result_type(DataType t1, DataType t2) {
    // Type promotion rules
    if (t1 == TYPE_DOUBLE || t2 == TYPE_DOUBLE) return TYPE_DOUBLE;
    if (t1 == TYPE_FLOAT || t2 == TYPE_FLOAT) return TYPE_FLOAT;
    if (t1 == TYPE_INT || t2 == TYPE_INT) return TYPE_INT;
    if (t1 == TYPE_CHAR || t2 == TYPE_CHAR) return TYPE_CHAR;
    return TYPE_UNKNOWN;
}

bool check_type_compatibility(DataType t1, DataType t2, int line) {
    if (t1 == TYPE_UNKNOWN || t2 == TYPE_UNKNOWN) {
        return false;
    }
    
    // Allow implicit conversions: char -> int -> float -> double
    if (t1 == t2) return true;
    
    if ((t1 == TYPE_CHAR && (t2 == TYPE_INT || t2 == TYPE_FLOAT || t2 == TYPE_DOUBLE)) ||
        (t2 == TYPE_CHAR && (t1 == TYPE_INT || t1 == TYPE_FLOAT || t1 == TYPE_DOUBLE))) {
        printf("[TYPE] Line %d: Implicit conversion between %s and %s\n", 
               line, type_to_string(t1), type_to_string(t2));
        return true;
    }
    
    if ((t1 == TYPE_INT && (t2 == TYPE_FLOAT || t2 == TYPE_DOUBLE)) ||
        (t2 == TYPE_INT && (t1 == TYPE_FLOAT || t1 == TYPE_DOUBLE))) {
        printf("[TYPE] Line %d: Implicit conversion between %s and %s\n", 
               line, type_to_string(t1), type_to_string(t2));
        return true;
    }
    
    if ((t1 == TYPE_FLOAT && t2 == TYPE_DOUBLE) ||
        (t2 == TYPE_FLOAT && t1 == TYPE_DOUBLE)) {
        printf("[TYPE] Line %d: Implicit conversion between %s and %s\n", 
               line, type_to_string(t1), type_to_string(t2));
        return true;
    }
    
    printf("[ERROR] Line %d: Type mismatch - cannot convert %s to %s\n", 
           line, type_to_string(t1), type_to_string(t2));
    error_count++;
    return false;
}

void print_symbol_table() {
    printf("\n=======================================================================\n");
    printf("SYMBOL TABLE\n");
    printf("=======================================================================\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Type", "Scope", "Line");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < symbol_table.count; i++) {
        printf("%-20s %-10s %-10d %-10d\n",
               symbol_table.symbols[i].name,
               type_to_string(symbol_table.symbols[i].type),
               symbol_table.symbols[i].scope_level,
               symbol_table.symbols[i].line_declared);
    }
    printf("=======================================================================\n\n");
}

void test_semantic_analyzer() {
    printf("=======================================================================\n");
    printf("MODULE 5: SEMANTIC ANALYSIS - TYPE & SCOPE CHECKING\n");
    printf("=======================================================================\n\n");
    
    init_semantic_analyzer();
    
    // Global scope
    printf("--- Global Scope ---\n");
    declare_symbol("x", TYPE_INT, 1);
    declare_symbol("y", TYPE_FLOAT, 2);
    declare_symbol("z", TYPE_DOUBLE, 3);
    
    // Enter new scope
    printf("\n--- Enter Block Scope ---\n");
    enter_scope();
    declare_symbol("a", TYPE_INT, 5);
    declare_symbol("b", TYPE_FLOAT, 6);
    
    // Test variable usage
    printf("\n--- Variable Usage ---\n");
    check_variable_declared("x", 7);  // Should find in global
    check_variable_declared("a", 8);  // Should find in current
    check_variable_declared("undefined", 9);  // Should error
    
    // Test type checking
    printf("\n--- Type Checking ---\n");
    Symbol* sym_x = lookup_symbol("x");
    Symbol* sym_y = lookup_symbol("y");
    if (sym_x && sym_y) {
        check_type_compatibility(sym_x->type, sym_y->type, 10);
    }
    
    // Test redeclaration in same scope
    printf("\n--- Redeclaration Test ---\n");
    declare_symbol("a", TYPE_DOUBLE, 11);  // Should error
    
    // Enter nested scope
    printf("\n--- Enter Nested Scope ---\n");
    enter_scope();
    declare_symbol("a", TYPE_CHAR, 13);  // OK - different scope
    declare_symbol("c", TYPE_INT, 14);
    
    // Exit nested scope
    printf("\n--- Exit Nested Scope ---\n");
    exit_scope();
    
    // Exit block scope
    printf("\n--- Exit Block Scope ---\n");
    exit_scope();
    
    // Print final symbol table
    print_symbol_table();
    
    printf("=======================================================================\n");
    printf("SEMANTIC ANALYSIS COMPLETE\n");
    printf("Total errors: %d\n", error_count);
    printf("=======================================================================\n");
}

int main() {
    test_semantic_analyzer();
    return 0;
}
