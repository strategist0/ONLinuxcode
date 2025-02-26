#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) ==

        sigaction(SIGCHLD, &sa, NULL) ==

        sigaction(SIGINT, &sa, NULL) ==

        sigaction(SIGQUIT, &sa, NULL) ==

        sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Try pressing Ctrl-C to exit.\n");
    sleep(10);
    printf("Exiting...\n");
    return 0;
}