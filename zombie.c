#include "zombie.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

static zombie_stats_t stats;

void sigchld_handler(int sig) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {
        stats.zombies_reaped++;
        stats.zombies_active--;
    }
}

void zombie_init(void) {
    stats.zombies_created = 0;
    stats.zombies_reaped = 0;
    stats.zombies_active = 0;
    signal(SIGCHLD, sigchld_handler);
}

pid_t zombie_safe_fork(void) {
    pid_t pid = fork();
    if (pid > 0) {
        stats.zombies_created++;
        stats.zombies_active++;
    }
    return pid;
}

int zombie_safe_spawn(const char *command, char *args[]) {
    pid_t pid = zombie_safe_fork();
    if (pid == 0) {
        execvp(command, args);
        exit(1);
    }
    return pid;
}

void zombie_get_stats(zombie_stats_t *out) {
    *out = stats;
}
