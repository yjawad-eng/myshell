#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"

static int log_fd = -1;
void init_logger(void){
  log_fd = open("myshell.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
if (log_fd < 0) perror("open myshell.log");
}

void log_command(pid_t pid, const char *raw, int status) {
  if (log_fd < 0) return;
char buf[1024];
int n = snprintf(buf, sizeof(buf), "[pid=%d] cmd=\"%s\" status=%d\n", (int)pid, raw, status);
if (n > 0) {
ssize_t w = write(log_fd, buf, (size_t)n);
(void)w;
  }
}
void close_logger(void) {
  if (log_fd >= 0) { close(log_fd); log_fd = -1;}
}
