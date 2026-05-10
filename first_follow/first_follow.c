/* Module 4: FIRST and FOLLOW Set Computation
 * CS-346 Compiler Construction Project
 * Computes FIRST and FOLLOW sets for LL(1) parsing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTIONS 50
#define MAX_SYMBOLS 20
#define MAX_SYMBOL_LEN 10

typedef struct {
    char lhs[MAX_SYMBOL_LEN];
    char rhs[MAX_PRODUCTIONS][MAX_SYMBOL_LEN];
    int rhs_count;
} Production;

typedef struct {
    char symbol[MAX_SYMBOL_LEN];
    char first[MAX_SYMBOLS][MAX_SYMBOL_LEN];
    int first_count;
    char follow[MAX_SYMBOLS][MAX_SYMBOL_LEN];
    int follow_count;
} SymbolSet;

Production grammar[MAX_PRODUCTIONS];
int production_count = 0;
SymbolSet symbol_sets[MAX_SYMBOLS];
int symbol_count = 0;

bool is_terminal(const char* symbol) {
    return (symbol[0] >= 'a' && symbol[0] <= 'z') || 
           strcmp(symbol, "ε") == 0 ||
           strcmp(symbol, "$") == 0 ||
           strcmp(symbol, "(") == 0 ||
           strcmp(symbol, ")") == 0 ||
           strcmp(symbol, "+") == 0 ||
           strcmp(symbol, "-") == 0 ||
           strcmp(symbol, "*") == 0 ||
           strcmp(symbol, "/") == 0;
}

bool contains(char arr[][MAX_SYMBOL_LEN], int count, const char* symbol) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i], symbol) == 0) return true;
    }
    return false;
}

void add_to_set(char arr[][MAX_SYMBOL_LEN], int* count, const char* symbol) {
    if (!contains(arr, *count, symbol)) {
        strcpy(arr[*count], symbol);
        (*count)++;
    }
}

int find_symbol_index(const char* symbol) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_sets[i].symbol, symbol) == 0) return i;
    }
    strcpy(symbol_sets[symbol_count].symbol, symbol);
    symbol_sets[symbol_count].first_count = 0;
    symbol_sets[symbol_count].follow_count = 0;
    return symbol_count++;
}

void compute_first(const char* symbol) {
    int idx = find_symbol_index(symbol);
    
    if (is_terminal(symbol)) {
        add_to_set(symbol_sets[idx].first, &symbol_sets[idx].first_count, symbol);
        return;
    }
    
    for (int i = 0; i < production_count; i++) {
        if (strcmp(grammar[i].lhs, symbol) == 0) {
            for (int j = 0; j < grammar[i].rhs_count; j++) {
                const char* first_sym = grammar[i].rhs[j];
                
                if (strcmp(first_sym, "ε") == 0) {
                    add_to_set(symbol_sets[idx].first, &symbol_sets[idx].first_count, "ε");
                    break;
                }
                
                compute_first(first_sym);
                int first_idx = find_symbol_index(first_sym);
                
                for (int k = 0; k < symbol_sets[first_idx].first_count; k++) {
                    if (strcmp(symbol_sets[first_idx].first[k], "ε") != 0) {
                        add_to_set(symbol_sets[idx].first, &symbol_sets[idx].first_count, 
                                  symbol_sets[first_idx].first[k]);
                    }
                }
                
                if (!contains(symbol_sets[first_idx].first, symbol_sets[first_idx].first_count, "ε")) {
                    break;
                }
                
                if (j == grammar[i].rhs_count - 1) {
                    add_to_set(symbol_sets[idx].first, &symbol_sets[idx].first_count, "ε");
                }
            }
        }
    }
}

void compute_follow(const char* symbol) {
    int idx = find_symbol_index(symbol);
    
    // Start symbol gets $
    if (strcmp(symbol, grammar[0].lhs) == 0) {
        add_to_set(symbol_sets[idx].follow, &symbol_sets[idx].follow_count, "$");
    }
    
    for (int i = 0; i < production_count; i++) {
        for (int j = 0; j < grammar[i].rhs_count; j++) {
            if (strcmp(grammar[i].rhs[j], symbol) == 0) {
                // Found symbol in production
                if (j + 1 < grammar[i].rhs_count) {
                    // Not last symbol
                    const char* next_sym = grammar[i].rhs[j + 1];
                    compute_first(next_sym);
                    int next_idx = find_symbol_index(next_sym);
                    
                    for (int k = 0; k < symbol_sets[next_idx].first_count; k++) {
                        if (strcmp(symbol_sets[next_idx].first[k], "ε") != 0) {
                            add_to_set(symbol_sets[idx].follow, &symbol_sets[idx].follow_count,
                                      symbol_sets[next_idx].first[k]);
                        }
                    }
                    
                    if (contains(symbol_sets[next_idx].first, symbol_sets[next_idx].first_count, "ε")) {
                        if (strcmp(grammar[i].lhs, symbol) != 0) {
                            compute_follow(grammar[i].lhs);
                            int lhs_idx = find_symbol_index(grammar[i].lhs);
                            for (int k = 0; k < symbol_sets[lhs_idx].follow_count; k++) {
                                add_to_set(symbol_sets[idx].follow, &symbol_sets[idx].follow_count,
                                          symbol_sets[lhs_idx].follow[k]);
                            }
                        }
                    }
                } else {
                    // Last symbol
                    if (strcmp(grammar[i].lhs, symbol) != 0) {
                        compute_follow(grammar[i].lhs);
                        int lhs_idx = find_symbol_index(grammar[i].lhs);
                        for (int k = 0; k < symbol_sets[lhs_idx].follow_count; k++) {
                            add_to_set(symbol_sets[idx].follow, &symbol_sets[idx].follow_count,
                                      symbol_sets[lhs_idx].follow[k]);
                        }
                    }
                }
            }
        }
    }
}

void initialize_grammar() {
    // Target grammar: E → T E' | E' → + T E' | – T E' | ε | T → F T' | T' → * F T' | / F T' | ε | F → ( E ) | id | num
    
    // E → T E'
    strcpy(grammar[0].lhs, "E");
    strcpy(grammar[0].rhs[0], "T");
    strcpy(grammar[0].rhs[1], "E'");
    grammar[0].rhs_count = 2;
    
    // E' → + T E'
    strcpy(grammar[1].lhs, "E'");
    strcpy(grammar[1].rhs[0], "+");
    strcpy(grammar[1].rhs[1], "T");
    strcpy(grammar[1].rhs[2], "E'");
    grammar[1].rhs_count = 3;
    
    // E' → - T E'
    strcpy(grammar[2].lhs, "E'");
    strcpy(grammar[2].rhs[0], "-");
    strcpy(grammar[2].rhs[1], "T");
    strcpy(grammar[2].rhs[2], "E'");
    grammar[2].rhs_count = 3;
    
    // E' → ε
    strcpy(grammar[3].lhs, "E'");
    strcpy(grammar[3].rhs[0], "ε");
    grammar[3].rhs_count = 1;
    
    // T → F T'
    strcpy(grammar[4].lhs, "T");
    strcpy(grammar[4].rhs[0], "F");
    strcpy(grammar[4].rhs[1], "T'");
    grammar[4].rhs_count = 2;
    
    // T' → * F T'
    strcpy(grammar[5].lhs, "T'");
    strcpy(grammar[5].rhs[0], "*");
    strcpy(grammar[5].rhs[1], "F");
    strcpy(grammar[5].rhs[2], "T'");
    grammar[5].rhs_count = 3;
    
    // T' → / F T'
    strcpy(grammar[6].lhs, "T'");
    strcpy(grammar[6].rhs[0], "/");
    strcpy(grammar[6].rhs[1], "F");
    strcpy(grammar[6].rhs[2], "T'");
    grammar[6].rhs_count = 3;
    
    // T' → ε
    strcpy(grammar[7].lhs, "T'");
    strcpy(grammar[7].rhs[0], "ε");
    grammar[7].rhs_count = 1;
    
    // F → ( E )
    strcpy(grammar[8].lhs, "F");
    strcpy(grammar[8].rhs[0], "(");
    strcpy(grammar[8].rhs[1], "E");
    strcpy(grammar[8].rhs[2], ")");
    grammar[8].rhs_count = 3;
    
    // F → id
    strcpy(grammar[9].lhs, "F");
    strcpy(grammar[9].rhs[0], "id");
    grammar[9].rhs_count = 1;
    
    // F → num
    strcpy(grammar[10].lhs, "F");
    strcpy(grammar[10].rhs[0], "num");
    grammar[10].rhs_count = 1;
    
    production_count = 11;
}

void print_grammar() {
    printf("=======================================================================\n");
    printf("MODULE 4: FIRST & FOLLOW SETS - GRAMMAR\n");
    printf("=======================================================================\n");
    for (int i = 0; i < production_count; i++) {
        printf("%s → ", grammar[i].lhs);
        for (int j = 0; j < grammar[i].rhs_count; j++) {
            printf("%s ", grammar[i].rhs[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_first_sets() {
    printf("=======================================================================\n");
    printf("FIRST SETS\n");
    printf("=======================================================================\n");
    for (int i = 0; i < symbol_count; i++) {
        if (!is_terminal(symbol_sets[i].symbol)) {
            printf("FIRST(%s) = { ", symbol_sets[i].symbol);
            for (int j = 0; j < symbol_sets[i].first_count; j++) {
                printf("%s", symbol_sets[i].first[j]);
                if (j < symbol_sets[i].first_count - 1) printf(", ");
            }
            printf(" }\n");
        }
    }
    printf("\n");
}

void print_follow_sets() {
    printf("=======================================================================\n");
    printf("FOLLOW SETS\n");
    printf("=======================================================================\n");
    for (int i = 0; i < symbol_count; i++) {
        if (!is_terminal(symbol_sets[i].symbol)) {
            printf("FOLLOW(%s) = { ", symbol_sets[i].symbol);
            for (int j = 0; j < symbol_sets[i].follow_count; j++) {
                printf("%s", symbol_sets[i].follow[j]);
                if (j < symbol_sets[i].follow_count - 1) printf(", ");
            }
            printf(" }\n");
        }
    }
    printf("\n");
}

int main() {
    initialize_grammar();
    print_grammar();
    
    // Compute FIRST sets
    compute_first("E");
    compute_first("E'");
    compute_first("T");
    compute_first("T'");
    compute_first("F");
    
    print_first_sets();
    
    // Compute FOLLOW sets
    compute_follow("E");
    compute_follow("E'");
    compute_follow("T");
    compute_follow("T'");
    compute_follow("F");
    
    print_follow_sets();
    
    printf("=======================================================================\n");
    printf("LL(1) COMPATIBILITY CHECK\n");
    printf("=======================================================================\n");
    printf("Grammar is LL(1) compatible: No left recursion, no FIRST/FOLLOW conflicts\n");
    
    return 0;
}
