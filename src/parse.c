#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse.h"

int parse_line(char *line, Job *job) {
    int argc = 0;
    int capacity = 8;

    job->background = 0;
    job->has_pipe = 0;
    job->rawline = NULL;

    job->left.argv = malloc(capacity * sizeof(char *));
    if (!job->left.argv)
        return -1;

    char *token = strtok(line, " \t");

    while (token) {
        if (strcmp(token, "&") == 0) {
            job->background = 1;
            token = strtok(NULL, " \t");
            continue;
        }

        if (argc >= capacity - 1) {
            capacity *= 2;
            char **tmp = realloc(job->left.argv,
                                  capacity * sizeof(char *));
            if (!tmp)
                return -1;
            job->left.argv = tmp;
        }

        job->left.argv[argc] = strdup(token);
        if (!job->left.argv[argc])
            return -1;

        argc++;
        token = strtok(NULL, " \t");
    }

    job->left.argv[argc] = NULL;
    return 0;
}

void free_job(Job *job) {
    if (!job)
        return;

    if (job->left.argv) {
        for (int i = 0; job->left.argv[i]; i++) {
            free(job->left.argv[i]);
        }
        free(job->left.argv);
    }
}
