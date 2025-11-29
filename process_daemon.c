#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void daemonize(void) {
    pid_t pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);

    setsid();
    signal(SIGCHLD, sigchld_handler);

    pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);

    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void spawn_workers(void) {
    while (1) {
        pid_t pid = fork();
        if (pid == 0) {
            // Hijo hace trabajo
            FILE *f = fopen("/tmp/daemon.log", "a");
            fprintf(f, "Worker PID %d doing work\n", getpid());
            fclose(f);
            exit(0);
        }
        sleep(5);
    }
}

int main() {
    daemonize();
    spawn_workers();
    return 0;
}
