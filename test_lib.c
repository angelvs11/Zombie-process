#include "zombie.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    zombie_init();
    char *args[] = {"sleep", "2", NULL};
    zombie_safe_spawn("sleep", args);

    sleep(3);

    zombie_stats_t stats;
    zombie_get_stats(&stats);

    printf("Zombies created: %d\n", stats.zombies_created);
    printf("Zombies reaped: %d\n", stats.zombies_reaped);
    printf("Active zombies: %d\n", stats.zombies_active);

    return 0;
}
