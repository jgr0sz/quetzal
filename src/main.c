#include "builtins.h"
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "parser.h"
#include "executor.h"

int main() {
    char *line = NULL;
    size_t len = 0;
    
    printf("%s", ASCII_LOGO);
    printf("Type 'exit' to quit.\n\n");
    
    while (1) {
        printf(PROMPT);
        if (getline(&line, &len, stdin) == -1) {
            printf("\n");
            break;
        }

        Command cmd;
        parse_line(line, &cmd);

        if (cmd.argc > 0) {
            if (!execute_builtin(&cmd)) {
                execute_command(&cmd);
            }
        }
    }
    free(line);
    return 0;
}