#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void reap_explicit(void) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void sigchld_handler(int sig) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void setup_auto_reaper(void) {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);
}

void setup_ignore_reaper(void) {
    signal(SIGCHLD, SIG_IGN);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <strategy 1|2|3>\n", argv[0]);
        return 1;
    }

    int strategy = atoi(argv[1]);

    for (int i = 0; i < 10; i++) {
        if (fork() == 0) {
            sleep(rand() % 3);
            exit(i);
        }
    }

    switch(strategy) {
        case 1: reap_explicit(); break;
        case 2: setup_auto_reaper(); break;
        case 3: setup_ignore_reaper(); break;
    }

    sleep(5); // Espera a los hijos
    system("ps aux | grep Z | grep -v grep");
    return 0;
}
