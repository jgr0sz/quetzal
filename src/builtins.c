// builtins handles a command by whether it is a builtin command (exit, cd) or
// not, returning 1 for the former and 0 for the latter

#include "builtins.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_builtin(Command *cmd) {
  if (cmd->argc == 0) {
    return 0;
  }

  if (strcmp(cmd->argv[0], "exit") == 0) {
    printf("Closing shell...\n");
    exit(0);
  }

  if (strcmp(cmd->argv[0], "cd") == 0) {
    // Get/check cd dir arg
    const char *dir = (cmd->argc >= 2) ? cmd->argv[1] : getenv("HOME");

    if (dir == NULL) {
      fprintf(stderr, SHELL_NAME ": cd: HOME env variable not set.\n");
    } else if (chdir(dir) != 0) {
      perror(SHELL_NAME ": cd");
    }
    return 1;
  }
  return 0;
}
