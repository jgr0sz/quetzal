// executor uses the parsed command from lexer.c, spawns a child process from
// the shell, and calls execvp() on it to run the program specified.
#include "parser.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_command(Command *cmd) {
  if (cmd->argc == 0) {
    return;
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork failed");
  } else if (pid == 0) {
    // Child process is spawned, replaced by program passed through Command cmd
    execvp(cmd->argv[0], cmd->argv);
    fprintf(stderr, SHELL_NAME ": command not found: %s\n", cmd->argv[0]);
    exit(COMMAND_NOT_FOUND);
  } else {
    // Waits until child process is finished
    waitpid(pid, NULL, 0);
  }
}