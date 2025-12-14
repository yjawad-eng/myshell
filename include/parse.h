#ifndef PARSE_H
#define PARSE_H
#include <stddef.h>

typedef struct {
char **argv;
char *in_file;
char *out_file;
int out_append;
}
Command;

typedef struct {
Command left;
Command right;
int has_pipe;
int background;
char *rawline;
} Job;

int parse_line(char *line, Job *job);
void free_job(Job *job);
#endif
