#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LEN 256

typedef enum {
    T_EOF,
    T_COMPONENT,
    T_INT,
    T_STRING_TYPE,
    T_IF,
    T_ELSE,
    T_WHILE,
    T_DO_WHILE,
    T_FOR,
    T_IMPORT,
    T_IDENT,
    T_NUMBER,
    T_STRING,
    T_LBRACE,
    T_RBRACE,
    T_LPAREN,
    T_RPAREN,
    T_SEMI,
    T_EQ,
    T_COLON,
    T_COMMA
} TokenType;

typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LEN];
} Token;

extern char source[4096];
extern int pos;
extern Token curtok;

void loadFile(const char *filename);
Token nextToken();

#endif