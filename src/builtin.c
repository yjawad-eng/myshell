


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
  const char *target = argv[1] ? argv[1] : getenv("HOME");
if (!target || chdir(target) != 0){
 perror("cd");
}
}
