#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int is_builtin(char **argv){
  if (!argv || !argv[0]) 
    return 0;
return strcmp(argv[0], "cd") == 0;
}

void run_builtin(char **argv) {
if(strcmp(argv[0], "cd") == 0) {
char *path = argv[1];
if (path == NULL) {
path = getenv("HOME");
if(!path) {
fprintf(stderr, "cd: HOME not set\n");
return;
}
}
if (chdir(path) != 0) {
perror("cd");
}
}
}

