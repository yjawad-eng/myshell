#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
int main(void) {
char line [1024];

while(1) {
printf("myshell> ");
fflush(stdout);

if (fgets(line, sizeof(line), stdin) == NULL) {
printf("\n");
break;
}

size_t len = strlen(line);
if (len > 0 && line[len-1] == '\n') {
line[len-1] = '\0';
}

if (strcmp(line, "exit") == 0 ||strcmp(line, "quit") == 0) {
break;
}
Job job;
memset(&job, 0, sizeof(Job));
if (parse_line(line, &job) != 0) {
fprintf(stderr, "parse error\n");
free_job(&job);
continue;
}
if (job.left.argv) {
for (int i=0; job.left.argv[i]; i++) {
printf("argv[%d] = %s\n", i, job.left.argv[i]);
}
}
free_job(&job);
}
return 0;
}
