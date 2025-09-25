#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include <string.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

void execute_command(const char *cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execlp("sh", "sh", "-c", cmd, (char *) NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    int fd, wd;
    char buffer[BUF_LEN];

    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    wd = inotify_add_watch(fd, "./components/", IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    printf("Iniciando vigilancia de la carpeta 'components'. Presiona Ctrl+C para salir.\n");
    
    while (1) {
        int length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->len) {
                // Ahora el watcher reacciona a 'IN_MODIFY' y a 'IN_CREATE'
                if (event->mask & (IN_MODIFY | IN_CREATE)) {
                    // Asegúrate de que sea un archivo .mn
                    if (strstr(event->name, ".mn") != NULL) {
                        char command[512];
                         execute_command("clear");
                        sprintf(command, "./moon-compiler ./components/%s", event->name);
                        
                        printf("¡Cambios detectados en %s! Compilando...\n", event->name);
                        execute_command(command);
                        printf("¡Proceso terminado! Refresca tu navegador para ver los cambios.\n");
                        printf("------------------------------------------------------------------\n");
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}