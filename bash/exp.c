#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 128
#define MAX_PIPES 10

void sigint_handler(int signo) {
    printf("\n[xxx-super-shell] Ctrl+C is disabled!\n");
}

void execute_command(char* cmd, int in_fd, int out_fd, int background) {
    static char prev_dir[MAX_CMD_LEN] = "";
    char* args[MAX_ARGS];
    int argc = 0;
    char *infile = NULL, *outfile = NULL;
    int append = 0;

    char* token = strtok(cmd, " ");
    while (token) {
        if (strcmp(token, "&") == 0) {
            background = 1;
        } else if (strcmp(token, "<") == 0) {
            infile = strtok(NULL, " ");
        } else if (strcmp(token, ">>") == 0) {
            outfile = strtok(NULL, " ");
            append = 1;
        } else if (strcmp(token, ">") == 0) {
            outfile = strtok(NULL, " ");
        } else {
            args[argc++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    if (argc == 0)
        return;

    if (strcmp(args[0], "cd") == 0) {
        char current_dir[MAX_CMD_LEN];

        if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
            perror("getcwd");
            return;
        }

        if (argc > 1) {
            if (strcmp(args[1], "-") == 0) {
                if (strlen(prev_dir) == 0) {
                    printf("xxx-super-shell: cd -: OLDPWD not set\n");
                    return;
                }
                printf("%s\n", prev_dir);
                chdir(prev_dir);
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                    return;
                }
            }
        } else {
            chdir(getenv("HOME"));
        }

        strcpy(prev_dir, current_dir);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (outfile) {
            int fd =
                open(outfile,
                     O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (!background) {
        waitpid(pid, NULL, 0);
    }
}

void run_shell() {
    signal(SIGINT, sigint_handler);
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("\033[1;32mxxx-super-shell> \033[0m");
        fflush(stdout);
        if (!fgets(cmd, MAX_CMD_LEN, stdin))
            break;
        cmd[strcspn(cmd, "\n")] = 0;

        char* commands[MAX_PIPES];
        int cmd_count = 0;
        char* token = strtok(cmd, "|");
        while (token) {
            commands[cmd_count++] = token;
            token = strtok(NULL, "|");
        }

        int in_fd = STDIN_FILENO;
        int fds[2];

        for (int i = 0; i < cmd_count; i++) {
            if (i < cmd_count - 1)
                pipe(fds);

            execute_command(commands[i], in_fd,
                            (i < cmd_count - 1) ? fds[1] : STDOUT_FILENO, 0);

            if (i > 0)
                close(in_fd);

            if (i < cmd_count - 1) {
                close(fds[1]);
                in_fd = fds[0];
            }
        }
    }
}

int main() {
    run_shell();
    return 0;
}