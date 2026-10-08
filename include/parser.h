#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64
#define COMMAND_NOT_FOUND 127

typedef struct {
    char *argv[MAX_ARGS];
    int argc;
} Command;

void parse_line(char *line, Command *cmd);

#endif