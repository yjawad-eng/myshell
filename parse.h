#ifndef PARSE_H
#define PARSE_H

typedef struct {
char **argv;
}
Command;
Command *parse_line(char *line);
voide free_command(Command *cmd);

#endif
