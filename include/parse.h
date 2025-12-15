#ifndef PARSE_H
#define PARSE_H
#include <stddef.h>

typedef struct {
    char **argv;
    char *input_file;
    char *output_file;
    int append;
} command_t;

typedef struct {
    command_t left;
    command_t right;
    int has_pipe;
    int background;
    char *raw_line;
} job_t;

int parse_line(char *line, job_t *job);
void free_job(job_t *job);
#endif
