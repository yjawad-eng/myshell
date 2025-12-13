#include <stdio.h>
#include <string.h>

int main(void) {
char line [1024];

while(1) {
printf("myshell> ");
fflush(stdout);

if (!fgets(line, sizeof(line), stdin))
break;

size_t len = strlen(line);
if (len > 0 && line[len-1] == '\n') {
line[len-1] = '\0';
}

if (strcmp(line, "exit") == 0 ||strcmp(line, "quit") == 0)
break;
}
return 0;
}
