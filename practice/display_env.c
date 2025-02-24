#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char* argv[]) {
    char** envp;
    for (envp = environ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    exit(EXIT_SUCCESS);
}