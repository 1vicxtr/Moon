#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/wait.h>

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

    wd = inotify_add_watch(fd, "./components/Home.mn", IN_MODIFY);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    printf("Iniciando vigilancia. Presiona Ctrl+C para salir.\n");
    
    while (1) {
        read(fd, buffer, BUF_LEN);
        execute_command("clear");
        printf("¡Cambios detectados! Ejecutando moon-compiler...\n");
        execute_command("./moon-compiler");

        printf("¡Proceso terminado! Refresca tu navegador para ver los cambios.\n");
        printf("------------------------------------------------------------------\n");
    }

    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}