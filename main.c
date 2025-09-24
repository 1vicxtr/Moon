#include "compiler/lexer.h"
#include "compiler/parser.h"
#include <stdio.h>

int main() {
    loadFile("./components/Home.mn");
    parseFile();
    return 0;
}