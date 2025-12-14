#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

void setup_shell_signals(void) {
    signal(SIGINT, SIG_IGN);
}

void restore_child_signals(void) {
    signal(SIGINT, SIG_DFL);
}
