%{
/* Module 1: Lexical Analyzer for CS-346 Compiler Project
 * NUST SEECS - BSCS-2023-AB
 * Instructors: Lab - Ms. Urooj Akmal, Theory - Dr. Ahmed Rathore
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_num = 1;
int token_count = 0;

void print_token(const char* type, const char* value);
unsigned int compute_hash(const char* str);

/* Token definitions for standalone lexer */
#define IF 258
#define THEN 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define DO 263
#define RETURN 264
#define BREAK 265
#define CONTINUE 266
#define INT 267
#define FLOAT 268
#define DOUBLE 269
#define CHAR 270
#define VOID 271
#define BEGIN_KW 272
#define END 273
#define PROCEDURE 274
#define FUNCTION 275
#define PLUS 276
#define MINUS 277
#define MULT 278
#define DIV 279
#define POW 280
#define ASSIGN 281
#define EQ 282
#define NE 283
#define LT 284
#define LE 285
#define GT 286
#define GE 287
#define AND 288
#define OR 289
#define NOT 290
#define LPAREN 291
#define RPAREN 292
#define LBRACE 293
#define RBRACE 294
#define SEMICOLON 295
#define COMMA 296
#define NUM 297
#define FNUM 298
#define ID 299
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID_START    [a-z]
IDENTIFIER  {ID_START}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+
WHITESPACE  [ \t]+
NEWLINE     \n

%%

    /* Keywords */
"if"            { print_token("KEYWORD", yytext); return IF; }
"then"          { print_token("KEYWORD", yytext); return THEN; }
"else"          { print_token("KEYWORD", yytext); return ELSE; }
"while"         { print_token("KEYWORD", yytext); return WHILE; }
"for"           { print_token("KEYWORD", yytext); return FOR; }
"do"            { print_token("KEYWORD", yytext); return DO; }
"return"        { print_token("KEYWORD", yytext); return RETURN; }
"break"         { print_token("KEYWORD", yytext); return BREAK; }
"continue"      { print_token("KEYWORD", yytext); return CONTINUE; }
"int"           { print_token("KEYWORD", yytext); return INT; }
"float"         { print_token("KEYWORD", yytext); return FLOAT; }
"double"        { print_token("KEYWORD", yytext); return DOUBLE; }
"char"          { print_token("KEYWORD", yytext); return CHAR; }
"void"          { print_token("KEYWORD", yytext); return VOID; }
"begin"         { print_token("KEYWORD", yytext); return BEGIN_KW; }
"end"           { print_token("KEYWORD", yytext); return END; }
"procedure"     { print_token("KEYWORD", yytext); return PROCEDURE; }
"function"      { print_token("KEYWORD", yytext); return FUNCTION; }

    /* Operators */
"+"             { print_token("OPERATOR", yytext); return PLUS; }
"-"             { print_token("OPERATOR", yytext); return MINUS; }
"*"             { print_token("OPERATOR", yytext); return MULT; }
"/"             { print_token("OPERATOR", yytext); return DIV; }
"^"             { print_token("OPERATOR", yytext); return POW; }
"="             { print_token("OPERATOR", yytext); return ASSIGN; }
"=="            { print_token("OPERATOR", yytext); return EQ; }
"!="            { print_token("OPERATOR", yytext); return NE; }
"<"             { print_token("OPERATOR", yytext); return LT; }
"<="            { print_token("OPERATOR", yytext); return LE; }
">"             { print_token("OPERATOR", yytext); return GT; }
">="            { print_token("OPERATOR", yytext); return GE; }
"&&"            { print_token("OPERATOR", yytext); return AND; }
"||"            { print_token("OPERATOR", yytext); return OR; }
"!"             { print_token("OPERATOR", yytext); return NOT; }

    /* Delimiters */
"("             { print_token("DELIMITER", yytext); return LPAREN; }
")"             { print_token("DELIMITER", yytext); return RPAREN; }
"{"             { print_token("DELIMITER", yytext); return LBRACE; }
"}"             { print_token("DELIMITER", yytext); return RBRACE; }
";"             { print_token("DELIMITER", yytext); return SEMICOLON; }
","             { print_token("DELIMITER", yytext); return COMMA; }

    /* Comments - discard */
"//".*          { /* Single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* Multi-line comment */ }

    /* Literals */
{INTEGER}       { print_token("INTEGER", yytext); return NUM; }
{FLOAT}         { print_token("FLOAT", yytext); return FNUM; }

    /* Identifiers */
{IDENTIFIER}    { print_token("IDENTIFIER", yytext); return ID; }

    /* Whitespace */
{WHITESPACE}    { /* Skip */ }
{NEWLINE}       { line_num++; }

    /* Unrecognized character */
.               { fprintf(stderr, "Error: Unrecognized character '%s' at line %d\n", yytext, line_num); }

%%

void print_token(const char* type, const char* value) {
    unsigned int hash = compute_hash(value);
    printf("%-15s %-20s Line: %-5d Hash: %u\n", type, value, line_num, hash);
    token_count++;
}

unsigned int compute_hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash += (unsigned char)(*str);
        str++;
    }
    return hash % 997;
}

int main(int argc, char** argv) {
    FILE* input = stdin;
    
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = input;
    }
    
    printf("=======================================================================\n");
    printf("MODULE 1: LEXICAL ANALYSIS - TOKEN TABLE\n");
    printf("=======================================================================\n");
    printf("%-15s %-20s %-11s %s\n", "Token Type", "Value", "Line", "Hash");
    printf("-----------------------------------------------------------------------\n");
    
    int token;
    while ((token = yylex()) != 0) {
        /* Tokens are printed in the rules above */
    }
    
    printf("=======================================================================\n");
    printf("Total tokens: %d\n", token_count);
    printf("=======================================================================\n");
    
    if (input != stdin) fclose(input);
    return 0;
}
