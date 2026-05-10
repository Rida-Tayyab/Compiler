/* Module 6: Intermediate Representation (IR) Generator
 * CS-346 Compiler Construction Project
 * Generates Three-Address Code (TAC)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAC 500
#define MAX_TEMP 100

typedef enum {
    TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,
    TAC_ASSIGN, TAC_COPY,
    TAC_GOTO, TAC_IF_GOTO,
    TAC_PARAM, TAC_CALL, TAC_RETURN,
    TAC_ARRAY_READ, TAC_ARRAY_WRITE,
    TAC_LABEL
} TACOpcode;

typedef struct {
    TACOpcode op;
    char result[20];
    char arg1[20];
    char arg2[20];
} TACInstruction;

TACInstruction tac[MAX_TAC];
int tac_count = 0;
int temp_count = 0;
int label_count = 0;

const char* opcode_to_string(TACOpcode op) {
    switch (op) {
        case TAC_ADD: return "+";
        case TAC_SUB: return "-";
        case TAC_MUL: return "*";
        case TAC_DIV: return "/";
        case TAC_ASSIGN: return "=";
        case TAC_COPY: return "=";
        case TAC_GOTO: return "goto";
        case TAC_IF_GOTO: return "if_goto";
        case TAC_PARAM: return "param";
        case TAC_CALL: return "call";
        case TAC_RETURN: return "return";
        case TAC_ARRAY_READ: return "[]";
        case TAC_ARRAY_WRITE: return "[]=";
        case TAC_LABEL: return "label";
        default: return "unknown";
    }
}

char* new_temp() {
    static char temp[20];
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char* new_label() {
    static char label[20];
    sprintf(label, "L%d", label_count++);
    return label;
}

void emit(TACOpcode op, const char* result, const char* arg1, const char* arg2) {
    if (tac_count >= MAX_TAC) {
        fprintf(stderr, "Error: TAC overflow\n");
        return;
    }
    
    tac[tac_count].op = op;
    strcpy(tac[tac_count].result, result ? result : "");
    strcpy(tac[tac_count].arg1, arg1 ? arg1 : "");
    strcpy(tac[tac_count].arg2, arg2 ? arg2 : "");
    tac_count++;
}

void print_tac() {
    printf("\n=======================================================================\n");
    printf("THREE-ADDRESS CODE (TAC)\n");
    printf("=======================================================================\n");
    
    for (int i = 0; i < tac_count; i++) {
        TACInstruction* inst = &tac[i];
        
        switch (inst->op) {
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
                printf("%3d: %s = %s %s %s\n", i, inst->result, inst->arg1, 
                       opcode_to_string(inst->op), inst->arg2);
                break;
            
            case TAC_ASSIGN:
            case TAC_COPY:
                printf("%3d: %s = %s\n", i, inst->result, inst->arg1);
                break;
            
            case TAC_GOTO:
                printf("%3d: goto %s\n", i, inst->result);
                break;
            
            case TAC_IF_GOTO:
                printf("%3d: if %s goto %s\n", i, inst->arg1, inst->result);
                break;
            
            case TAC_PARAM:
                printf("%3d: param %s\n", i, inst->result);
                break;
            
            case TAC_CALL:
                printf("%3d: %s = call %s, %s\n", i, inst->result, inst->arg1, inst->arg2);
                break;
            
            case TAC_RETURN:
                printf("%3d: return %s\n", i, inst->result);
                break;
            
            case TAC_ARRAY_READ:
                printf("%3d: %s = %s[%s]\n", i, inst->result, inst->arg1, inst->arg2);
                break;
            
            case TAC_ARRAY_WRITE:
                printf("%3d: %s[%s] = %s\n", i, inst->result, inst->arg1, inst->arg2);
                break;
            
            case TAC_LABEL:
                printf("%s:\n", inst->result);
                break;
        }
    }
    
    printf("=======================================================================\n");
}

void generate_expression_tac() {
    // Example: a = b + c * d
    // TAC:
    //   t0 = c * d
    //   t1 = b + t0
    //   a = t1
    
    char* t0 = new_temp();
    char* t1 = new_temp();
    
    emit(TAC_MUL, t0, "c", "d");
    emit(TAC_ADD, t1, "b", t0);
    emit(TAC_COPY, "a", t1, NULL);
}

void generate_if_tac() {
    // Example: if (x > 5) y = 10; else y = 20;
    // TAC:
    //   if x > 5 goto L0
    //   y = 20
    //   goto L1
    // L0:
    //   y = 10
    // L1:
    
    char* L0 = new_label();
    char* L1 = new_label();
    
    emit(TAC_IF_GOTO, L0, "x > 5", NULL);
    emit(TAC_COPY, "y", "20", NULL);
    emit(TAC_GOTO, L1, NULL, NULL);
    emit(TAC_LABEL, L0, NULL, NULL);
    emit(TAC_COPY, "y", "10", NULL);
    emit(TAC_LABEL, L1, NULL, NULL);
}

void generate_loop_tac() {
    // Example: while (i < 10) { sum = sum + i; i = i + 1; }
    // TAC:
    // L0:
    //   if i < 10 goto L1
    //   goto L2
    // L1:
    //   t0 = sum + i
    //   sum = t0
    //   t1 = i + 1
    //   i = t1
    //   goto L0
    // L2:
    
    char* L0 = new_label();
    char* L1 = new_label();
    char* L2 = new_label();
    char* t0 = new_temp();
    char* t1 = new_temp();
    
    emit(TAC_LABEL, L0, NULL, NULL);
    emit(TAC_IF_GOTO, L1, "i < 10", NULL);
    emit(TAC_GOTO, L2, NULL, NULL);
    emit(TAC_LABEL, L1, NULL, NULL);
    emit(TAC_ADD, t0, "sum", "i");
    emit(TAC_COPY, "sum", t0, NULL);
    emit(TAC_ADD, t1, "i", "1");
    emit(TAC_COPY, "i", t1, NULL);
    emit(TAC_GOTO, L0, NULL, NULL);
    emit(TAC_LABEL, L2, NULL, NULL);
}

void generate_function_call_tac() {
    // Example: result = foo(x, y)
    // TAC:
    //   param x
    //   param y
    //   t0 = call foo, 2
    //   result = t0
    
    char* t0 = new_temp();
    
    emit(TAC_PARAM, "x", NULL, NULL);
    emit(TAC_PARAM, "y", NULL, NULL);
    emit(TAC_CALL, t0, "foo", "2");
    emit(TAC_COPY, "result", t0, NULL);
}

void generate_array_tac() {
    // Example: a[i] = b[j] + 5
    // TAC:
    //   t0 = b[j]
    //   t1 = t0 + 5
    //   a[i] = t1
    
    char* t0 = new_temp();
    char* t1 = new_temp();
    
    emit(TAC_ARRAY_READ, t0, "b", "j");
    emit(TAC_ADD, t1, t0, "5");
    emit(TAC_ARRAY_WRITE, "a", "i", t1);
}

int main() {
    printf("=======================================================================\n");
    printf("MODULE 6: INTERMEDIATE REPRESENTATION (IR) GENERATION\n");
    printf("=======================================================================\n");
    
    printf("\n--- Example 1: Expression ---\n");
    printf("Source: a = b + c * d\n");
    generate_expression_tac();
    print_tac();
    
    tac_count = 0;
    temp_count = 0;
    label_count = 0;
    
    printf("\n--- Example 2: If-Else Statement ---\n");
    printf("Source: if (x > 5) y = 10; else y = 20;\n");
    generate_if_tac();
    print_tac();
    
    tac_count = 0;
    temp_count = 0;
    label_count = 0;
    
    printf("\n--- Example 3: While Loop ---\n");
    printf("Source: while (i < 10) { sum = sum + i; i = i + 1; }\n");
    generate_loop_tac();
    print_tac();
    
    tac_count = 0;
    temp_count = 0;
    label_count = 0;
    
    printf("\n--- Example 4: Function Call ---\n");
    printf("Source: result = foo(x, y)\n");
    generate_function_call_tac();
    print_tac();
    
    tac_count = 0;
    temp_count = 0;
    label_count = 0;
    
    printf("\n--- Example 5: Array Operations ---\n");
    printf("Source: a[i] = b[j] + 5\n");
    generate_array_tac();
    print_tac();
    
    return 0;
}
