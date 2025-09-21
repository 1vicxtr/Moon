#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define COMPONENTS_FOLDER "components"
#define OUTPUT_FILE "bundle.js"
#define MAX_LINE 1024
#define MAX_PATH 512

void compile_moon_file(const char *filepath, FILE *out) {
    FILE *in = fopen(filepath, "r");
    if (!in) {
        printf("Error al abrir %s\n", filepath);
        return;
    }

    char line[MAX_LINE];
    char component_name[256];

    // Nombre del componente = nombre del archivo sin extensión
    const char *fname = strrchr(filepath, '/');
    if (!fname) fname = filepath; else fname++;
    strncpy(component_name, fname, sizeof(component_name));
    char *dot = strrchr(component_name, '.');
    if (dot) *dot = '\0';

    fprintf(out, "function %s() {\n", component_name);
    fprintf(out, "  const div = document.createElement('div');\n");

    while (fgets(line, sizeof(line), in)) {
        // Quitamos salto de línea
        line[strcspn(line, "\r\n")] = 0;
        // Agregamos línea al innerHTML
        fprintf(out, "  div.innerHTML += `%s`;\n", line);
    }

    fprintf(out, "  return div;\n");
    fprintf(out, "}\n\n");

    fclose(in);
}

int main() {
    DIR *d;
    struct dirent *entry;
    FILE *out = fopen(OUTPUT_FILE, "w");
    if (!out) {
        printf("No se pudo crear %s\n", OUTPUT_FILE);
        return 1;
    }

    d = opendir(COMPONENTS_FOLDER);
    if (!d) {
        printf("No se pudo abrir la carpeta %s\n", COMPONENTS_FOLDER);
        return 1;
    }

    while ((entry = readdir(d)) != NULL) {
        if (entry->d_type == DT_REG) {
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".moon") == 0) {
                char filepath[MAX_PATH];
                snprintf(filepath, sizeof(filepath), "%s/%s", COMPONENTS_FOLDER, entry->d_name);
                compile_moon_file(filepath, out);
            }
        }
    }

    closedir(d);
    fclose(out);

    printf("Bundle generado: %s\n", OUTPUT_FILE);
    return 0;
}
