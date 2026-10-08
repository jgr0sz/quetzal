// lexer takes a raw string, such as "ls -a /tmp\n", strips the newline, and
// splits each part of the command into tokens stored in cmd->argv. NULL must be
// added ahead of execvp().
#include "parser.h"
#include <string.h>
void parse_line(char *line, Command *cmd) {
  if (line == NULL || cmd == NULL) {
    return;
  }

  // Strip trailing newline
  line[strcspn(line, "\r\n")] = '\0';
  cmd->argc = 0;

  char *token = strtok(line, " \t");

  while (token != NULL && cmd->argc < MAX_ARGS - 1) {
    cmd->argv[cmd->argc] = token;
    cmd->argc++;
    token = strtok(NULL, " ");
  }
  cmd->argv[cmd->argc] = NULL;
}
