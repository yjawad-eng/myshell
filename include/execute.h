#ifndef EXECUTE_H
#define EXECUTE_H
#define
#include <sys/types.h>
#include "parse.h"
int execute_job(const Job *job, pid_t *fg_pid_out, int *exit_status_out);
#endif
