/* Dummy header for standalone lexer compilation */
#ifndef PARSER_TAB_H
#define PARSER_TAB_H

typedef union {
    int ival;
    float fval;
    char* sval;
} YYSTYPE;

extern YYSTYPE yylval;

/* Token definitions */
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

#endif
