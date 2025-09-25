#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Incluye el resto de tus archivos del compilador
#include "compiler/lexer.h"
#include "compiler/parser.h"

int main() {
    DIR *dir;
    struct dirent *ent;

    // Abre el archivo de salida una sola vez
    FILE* outputFile = fopen("bundle.js", "w");
    if (!outputFile) {
        fprintf(stderr, "Error: No se puede crear el archivo bundle.js\n");
        return 1;
    }

    if ((dir = opendir("./components/")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".mn") != NULL) {
                char filePath[512];
                snprintf(filePath, sizeof(filePath), "./components/%s", ent->d_name);
                
                printf("Compilando %s...\n", ent->d_name);
                
                // Le dice al parser que va a compilar un nuevo archivo
                fprintf(outputFile, "// Compilado desde %s\n", ent->d_name);
                
                // REINICIA LA POSICIÓN DEL LEXER
                pos = 0;
                
                loadFile(filePath);
                parseFile(outputFile);
                
                printf("----------------------------------------\n");
            }
        }
        closedir(dir);
    } else {
        perror("Error al abrir el directorio components/");
        return 1;
    }

    // Cierra el archivo una sola vez, al final de todo el proceso
    fclose(outputFile);

    return 0;
}