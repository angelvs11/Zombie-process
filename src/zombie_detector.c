#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int find_zombies(int *zombie_pids, int max_zombies) {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir /proc failed");
        return -1;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(proc)) != NULL && count < max_zombies) {
        if (!isdigit(entry->d_name[0])) continue;

        char path[1024];
	snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);

        FILE *f = fopen(path, "r");
        if (!f) continue;

        int pid, ppid;
        char comm[256], state;
        fscanf(f, "%d %s %c %d", &pid, comm, &state, &ppid);
        fclose(f);

        if (state == 'Z') {
            zombie_pids[count++] = pid;
        }
    }

    closedir(proc);
    return count;
}

void print_zombie_info(int pid) {
    char path[256];
    sprintf(path, "/proc/%d/stat", pid);

    FILE *f = fopen(path, "r");
    if (!f) return;

    int ppid;
    char comm[256], state;
    fscanf(f, "%*d %s %c %d", comm, &state, &ppid);
    fclose(f);

    printf("%-7d %-7d %-15s %-5c\n", pid, ppid, comm, state);
}

int main() {
    int zombie_pids[1024];
    int total = find_zombies(zombie_pids, 1024);

    printf("=== Zombie Process Report ===\n");
    printf("Total Zombies: %d\n\n", total);
    printf("PID     PPID    Command         State\n");
    printf("-----   -----   -------------  -----\n");

    for (int i = 0; i < total; i++)
        print_zombie_info(zombie_pids[i]);

    return 0;
}
