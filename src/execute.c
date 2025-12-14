#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "execute.h"

void execute_job(Job *job) {
    pid_t pid;
    int status;

    if (!job || !job->left.argv || !job->left.argv[0])
        return;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        /* Child process */
        execvp(job->left.argv[0], job->left.argv);
        perror("execvp");
        _exit(1);
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}
