#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024
#define MAX_PIPES 10
#define MAX_ARGS 64

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"

void run_shell(char* cmd) {
    signal_set();

    char* cmd[MAX_CMD_LEN];

    while (1) {
        printf(RED "lowshell>" RESET);
        fflush(stdout);
        if (!fgets(cmd, MAX_CMD_LEN, stdin))
            break;
        cmd[strcspn(cmd, "\n")] = 0;

        char* commands[MAX_PIPES];
        int num_commands = 0;
        char* token = strtok(cmd, "|");
        while (token) {
            commands[num_commands++] = token;
            token = strtok(NULL, "|");
        }

        int in_fd = STDIN_FILENO;
        int fds[2];

        for (int i = 0; i < num_commands; i++) {
            if (i < num_commands - 1)
                pipe(fds);
            execute_command(commands[i], in_fd,
                            (i < num_commands - 1) ? fds[1] : STDOUT_FILENO, 0);
            if (i > 0)
                close(in_fd);
            close(fds[1]);
            in_fd = fds[0];
        }
    }
}