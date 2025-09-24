#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *validTags[] = {
    "p",
    "h1",
    "h2",
    "div",
    "span",
    "a",
    "img",
    "ul",
    "li",
    "br",
    "strong",
    "em",
    "hr",
    "form",
    "input",
    "button",
    "label",
    "video",
    "audio",
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

FILE *outputFile;

void parseFile() {
    outputFile = fopen("bundle.js", "w");
    if (!outputFile) {
        printf("Error: No se puede crear el archivo bundle.js\n");
        return;
    }

    curtok = nextToken();
    while (curtok.type != T_EOF) {
        switch (curtok.type) {
            case T_COMPONENT:
                curtok = nextToken();
                if (curtok.type == T_IDENT) {
                    fprintf(outputFile, "function %s() {\n", curtok.text);
                    curtok = nextToken();
                }
                break;
            case T_STRING_TYPE:
            case T_INT:
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
                break;
            case T_RBRACE:
                fprintf(outputFile, "}\n");
                break;
            case T_IDENT:
                {
                    char tagName[MAX_TOKEN_LEN];
                    strcpy(tagName, curtok.text);
                    if (!isValidTag(tagName)) {
                        fprintf(stderr, "Error: Etiqueta HTML no válida: %s\n", tagName);
                        exit(1);
                    }
                    
                    curtok = nextToken();
                    if (curtok.type == T_LPAREN) {
                        char finalHtml[4096] = "";
                        char *htmlPtr = finalHtml;
                        char textContent[MAX_TOKEN_LEN] = "";

                        // Bucle para procesar atributos
                        while (curtok.type != T_RPAREN && curtok.type != T_EOF) {
                            curtok = nextToken();
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
                                            // Lógica para otros atributos, si es necesario
                                        }
                                    }
                                }
                            }
                            curtok = nextToken();
                            if(curtok.type == T_COMMA) {
                                curtok = nextToken();
                            }
                        }

                        // Genera el código para la etiqueta
                        if (strlen(textContent) > 0) {
                            fprintf(outputFile, "    document.body.innerHTML += `<%s>%s</%s>`;\n", tagName, textContent, tagName);
                        } else {
                            fprintf(outputFile, "    document.body.innerHTML += `<%s></%s>`;\n", tagName, tagName);
                        }
                    }
                }
                break;
            default:
                break;
        }
        curtok = nextToken();
    }
    fclose(outputFile);
}