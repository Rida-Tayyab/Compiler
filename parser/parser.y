%{
/* Module 2 & 3: Syntax Analyzer (Parser) for CS-346 Compiler Project
 * Supports: Infix, Prefix, Postfix expressions
 * Extended grammar with functions, exponentiation, log, exp
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void yyerror(const char* s);
int yylex(void);

extern int line_num;
%}

%union {
    int ival;
    float fval;
    char* sval;
}

%token <ival> NUM
%token <fval> FNUM
%token <sval> ID
%token IF THEN ELSE WHILE FOR DO RETURN BREAK CONTINUE
%token INT FLOAT DOUBLE CHAR VOID BEGIN_KW END PROCEDURE FUNCTION
%token PLUS MINUS MULT DIV POW ASSIGN
%token EQ NE LT LE GT GE AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA

%left PLUS MINUS
%left MULT DIV
%right POW
%right UMINUS

%type <fval> expr term factor base

%%

program:
    /* empty */
    | statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    expr SEMICOLON          { printf("Result: %f\n", $1); }
    | declaration SEMICOLON
    | assignment SEMICOLON
    | LBRACE statement_list RBRACE
    | error SEMICOLON       { yyerror("Invalid statement"); yyerrok; }
    ;

declaration:
    INT ID                  { printf("Declared int variable: %s\n", $2); free($2); }
    | FLOAT ID              { printf("Declared float variable: %s\n", $2); free($2); }
    | DOUBLE ID             { printf("Declared double variable: %s\n", $2); free($2); }
    ;

assignment:
    ID ASSIGN expr          { printf("Assignment: %s = %f\n", $1, $3); free($1); }
    ;

/* Extended Grammar (Module 3)
 * E → E + T | E – T | T
 * T → T * F | T / F | F
 * F → B ^ F | B
 * B → ( E ) | id | num | log( E ) | exp( E )
 */

expr:
    expr PLUS term          { $$ = $1 + $3; }
    | expr MINUS term       { $$ = $1 - $3; }
    | term                  { $$ = $1; }
    ;

term:
    term MULT factor        { $$ = $1 * $3; }
    | term DIV factor       { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | factor                { $$ = $1; }
    ;

factor:
    base POW factor         { $$ = pow($1, $3); }  /* Right-associative */
    | base                  { $$ = $1; }
    ;

base:
    LPAREN expr RPAREN      { $$ = $2; }
    | NUM                   { $$ = (float)$1; }
    | FNUM                  { $$ = $1; }
    | ID                    { 
        /* Variable lookup would go here */
        printf("Variable reference: %s\n", $1);
        $$ = 0;  /* Placeholder */
        free($1);
    }
    | MINUS base %prec UMINUS { $$ = -$2; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", line_num, s);
}

int main(int argc, char** argv) {
    printf("=======================================================================\n");
    printf("MODULE 2 & 3: SYNTAX ANALYSIS (PARSER)\n");
    printf("=======================================================================\n");
    
    #ifdef YYDEBUG
    yydebug = 1;
    #endif
    
    return yyparse();
}
