#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *validTags[] = {
    "p", "h1", "h2", "div", "span", "a", "img", "ul", "ol", "li", "br",
    "strong", "em", "form", "input", "button", "label", "video", "audio",
    NULL
};

int isValidTag(const char *tagName) {
    for (int i = 0; validTags[i] != NULL; i++) {
        if (strcmp(tagName, validTags[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void parseFile(FILE* outputFile) {
    curtok = nextToken();
    if (curtok.type == T_COMPONENT) {
        curtok = nextToken();
        if (curtok.type == T_IDENT) {
            char componentName[MAX_TOKEN_LEN];
            strcpy(componentName, curtok.text);
            fprintf(outputFile, "function %s() {\n", componentName);
            
            curtok = nextToken();
            if (curtok.type == T_LBRACE) {
                curtok = nextToken();
                while (curtok.type != T_RBRACE && curtok.type != T_EOF) {
                    if (curtok.type == T_STRING_TYPE || curtok.type == T_INT) {
                        curtok = nextToken();
                        if (curtok.type == T_IDENT) {
                            fprintf(outputFile, "    let %s", curtok.text);
                            curtok = nextToken();
                            if (curtok.type == T_EQ) {
                                curtok = nextToken();
                                if (curtok.type == T_STRING) {
                                    fprintf(outputFile, " = \"%s\";\n", curtok.text);
                                } else if (curtok.type == T_NUMBER) {
                                    fprintf(outputFile, " = %s;\n", curtok.text);
                                }
                            }
                        }
                    } else if (curtok.type == T_IDENT && isValidTag(curtok.text)) {
                        char tagName[MAX_TOKEN_LEN];
                        strcpy(tagName, curtok.text);
                        char textContent[MAX_TOKEN_LEN] = "";
                        char attributeString[MAX_TOKEN_LEN] = "";

                        curtok = nextToken();
                        if (curtok.type == T_LPAREN) {
                            curtok = nextToken();
                            while (curtok.type != T_RPAREN && curtok.type != T_EOF) {
                                if (curtok.type == T_IDENT) {
                                    char attrName[MAX_TOKEN_LEN];
                                    strcpy(attrName, curtok.text);
                                    curtok = nextToken();
                                    if (curtok.type == T_COLON) {
                                        curtok = nextToken();
                                        if (curtok.type == T_STRING) {
                                            if (strcmp(attrName, "text") == 0) {
                                                strcpy(textContent, curtok.text);
                                            } else {
                                                strcat(attributeString, " ");
                                                strcat(attributeString, attrName);
                                                strcat(attributeString, "=\"");
                                                strcat(attributeString, curtok.text);
                                                strcat(attributeString, "\"");
                                            }
                                        }
                                    }
                                }
                                curtok = nextToken();
                                if (curtok.type == T_COMMA) {
                                    curtok = nextToken();
                                }
                            }
                        }
                        
                        if (strlen(textContent) > 0) {
                            fprintf(outputFile, "    document.body.innerHTML += `<%s%s>%s</%s>`;\n", tagName, attributeString, textContent, tagName);
                        } else {
                            fprintf(outputFile, "    document.body.innerHTML += `<%s%s/>`;\n", tagName, attributeString);
                        }
                    }
                    curtok = nextToken();
                }
                fprintf(outputFile, "}\n");
            }
        }
    } else {
        fprintf(stderr, "Error: Se esperaba 'component' al inicio del archivo.\n");
    }
}