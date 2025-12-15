#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "execute.h"
#include "builtin.h"
#include "logger.h"
void execute_job(job_t *job)
{
    if (!job->has_pipe) {
        pid_t pid = fork();

        if (pid == 0) {
            if (job->left.input_file) {
                int fd = open(job->left.input_file, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }

            if (job->left.output_file) {
                int flags = O_WRONLY | O_CREAT |
                    (job->left.append ? O_APPEND : O_TRUNC);
                int fd = open(job->left.output_file, flags, 0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execvp(job->left.argv[0], job->left.argv);
            perror("execvp");
            exit(1);
        }

        if (!job->background)
            waitpid(pid, NULL, 0);

        log_command(pid, job->raw_line, 0);
        return;
    }

    /* ---------- PIPE CASE ---------- */

    int pipefd[2];
    pipe(pipefd);

    pid_t left = fork();
    if (left == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        execvp(job->left.argv[0], job->left.argv);
        perror("execvp left");
        exit(1);
    }

    pid_t right = fork();
    if (right == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);

        execvp(job->right.argv[0], job->right.argv);
        perror("execvp right");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    if (!job->background) {
        waitpid(left, NULL, 0);
        waitpid(right, NULL, 0);
    }

    log_command(left, job->raw_line, 0);
}
