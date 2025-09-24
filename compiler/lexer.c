#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char source[4096];
int pos = 0;
Token curtok;

void loadFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open %s\n", filename);
        return;
    }
    size_t n = fread(source, 1, sizeof(source)-1, f);
    source[n] = '\0';
    fclose(f);
}

TokenType matchKeyword(const char *s) {
    if (strcmp(s,"component")==0) return T_COMPONENT;
    if (strcmp(s,"int")==0) return T_INT;
    if (strcmp(s,"string")==0) return T_STRING_TYPE;
    if (strcmp(s,"if")==0) return T_IF;
    if (strcmp(s,"else")==0) return T_ELSE;
    if (strcmp(s,"while")==0) return T_WHILE;
    if (strcmp(s,"do")==0) return T_DO_WHILE;
    if (strcmp(s,"for")==0) return T_FOR;
    if (strcmp(s,"import")==0) return T_IMPORT;
    return T_IDENT;
}

Token nextToken() {
    Token tok;
    tok.type = T_EOF;
    tok.text[0] = '\0';

    while (isspace(source[pos])) pos++;

    char c = source[pos];
    if (c=='\0') {
        tok.type = T_EOF;
        return tok;
    }

    switch(c){
        case '{': tok.type=T_LBRACE; strcpy(tok.text,"{"); pos++; return tok;
        case '}': tok.type=T_RBRACE; strcpy(tok.text,"}"); pos++; return tok;
        case '(': tok.type=T_LPAREN; strcpy(tok.text,"("); pos++; return tok;
        case ')': tok.type=T_RPAREN; strcpy(tok.text,")"); pos++; return tok;
        case ';': tok.type=T_SEMI; strcpy(tok.text,";"); pos++; return tok;
        case '=': tok.type=T_EQ; strcpy(tok.text,"="); pos++; return tok;
        case ':': tok.type=T_COLON; strcpy(tok.text,":"); pos++; return tok;
        case ',': tok.type=T_COMMA; strcpy(tok.text,","); pos++; return tok;
        case '"': {
            pos++;
            int i=0;
            while(source[pos]!='"' && source[pos]!='\0' && i < MAX_TOKEN_LEN - 1) {
                tok.text[i++] = source[pos++];
            }
            tok.text[i]='\0';
            if(source[pos]=='"') pos++;
            tok.type = T_STRING;
            return tok;
        }
    }

    if (isalpha(c) || c=='_') {
        int i=0;
        while (isalnum(source[pos]) || source[pos]=='_' && i < MAX_TOKEN_LEN - 1) {
            tok.text[i++] = source[pos++];
        }
        tok.text[i]='\0';
        tok.type = matchKeyword(tok.text);
        return tok;
    }

    if (isdigit(c)) {
        int i=0;
        while (isdigit(source[pos]) && i < MAX_TOKEN_LEN - 1) {
            tok.text[i++] = source[pos++];
        }
        tok.text[i]='\0';
        tok.type = T_NUMBER;
        return tok;
    }

    pos++;
    return tok;
}