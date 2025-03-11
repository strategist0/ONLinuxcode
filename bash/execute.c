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
                    printf("Lowshell: cd -: OLDPWD not set\n");
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