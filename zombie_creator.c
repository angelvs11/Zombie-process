#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Creates N zombie processes
 */
int create_zombies(int count) {
    pid_t pid;

    for (int i = 0; i < count; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            return -1;
        }
        if (pid == 0) {
            // Hijo termina inmediatamente con código de salida i
            exit(i);
        } else {
            // Padre imprime PID del zombie
            printf("Created zombie: PID %d (exit code %d)\n", pid, i);
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_zombies>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    create_zombies(count);

    printf("Press Enter to exit and clean up zombies...\n");
    getchar();  // Mantener padre vivo
    return 0;
}
