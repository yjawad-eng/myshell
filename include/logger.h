#ifndef LOGGER_H
#define LOGGER_H
#include <sys/types.h>
void log_command(pid_t pid, const char *cmd, int status);
void close_logger(void);
#endif
