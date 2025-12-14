#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "execute.h"
#include "signals.h"
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

    /* Child */
    if (pid == 0) {
        restore_child_signals();
        execvp(job->left.argv[0], job->left.argv);
        perror("execvp");
        exit(1);
    }

    /* Parent */
    if (job->background) {
        printf("[bg] started pid %d\n", pid);
    } else {
        waitpid(pid, &status, 0);
    }
}
