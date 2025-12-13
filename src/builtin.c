int is_builtin(const Job job) {
  char *cmd = job.left.argv ? job.left.argv[0] : NULL;
return cmd && (!strcmp(cmd,"cd") || !strcmp(cmd, "exit"));
}
void run_builtin(const Job *job){
  const char *cmd = job->left.argv[0]
if(!strcmp(cmd, "cd")) {
const char *target = job->left.argv[1] ? job->left.argv[1] : getenv("HOME");
if(!target || chdir(target) != 0) perror("cd");
} else if (!strcmp(cmd, "exit" )){
exit(0);
  }
}
void log_command(const char *line) {
  static int fd = -1;
if (fd == -1) {
fd = open("myshell.log" ,  O_
