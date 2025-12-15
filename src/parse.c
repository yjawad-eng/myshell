#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"

#define INITIAL_ARGV_SIZE 8

/* helper to build argv */
static void add_arg(char ***argv, int *argc, int *capacity, char *arg)
{
    if (*argc >= *capacity - 1) {
        *capacity *= 2;
        *argv = realloc(*argv, (*capacity) * sizeof(char *));
    }
    (*argv)[(*argc)++] = strdup(arg);
    (*argv)[*argc] = NULL;
}

/* parse a single command (no pipes) */
static void parse_command(char *cmd, command_t *out)
{
    int argc = 0;
    int capacity = INITIAL_ARGV_SIZE;
    char *token;

    out->argv = malloc(capacity * sizeof(char *));
    out->argv[0] = NULL;
    out->input_file = NULL;
    out->output_file = NULL;
    out->append = 0;

    token = strtok(cmd, " \t");

    while (token) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token)
                out->input_file = strdup(token);
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t");
            if (token) {
                out->output_file = strdup(token);
                out->append = 0;
            }
        } else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t");
            if (token) {
                out->output_file = strdup(token);
                out->append = 1;
            }
        } else {
            add_arg(&out->argv, &argc, &capacity, token);
        }

        token = strtok(NULL, " \t");
    }
}

/* main entry */
int parse_line(char *line, job_t *job)
{
    char *pipe_pos;

    memset(job, 0, sizeof(job_t));
    job->raw_line = strdup(line);

    /* background job */
    char *amp = strchr(line, '&');
    if (amp) {
        job->background = 1;
        *amp = '\0';
    }

    /* pipe */
    pipe_pos = strchr(line, '|');
    if (pipe_pos) {
        job->has_pipe = 1;
        *pipe_pos = '\0';
        parse_command(line, &job->left);
        parse_command(pipe_pos + 1, &job->right);
    } else {
        job->has_pipe = 0;
        parse_command(line, &job->left);
    }

    return 0;
}

void free_job(job_t *job)
{
    command_t *cmds[2] = { &job->left, &job->right };

    for (int i = 0; i < 2; i++) {
        if (!cmds[i]->argv)
            continue;

        for (int j = 0; cmds[i]->argv[j]; j++)
            free(cmds[i]->argv[j]);

        free(cmds[i]->argv);
        free(cmds[i]->input_file);
        free(cmds[i]->output_file);
    }

    free(job->raw_line);
}
