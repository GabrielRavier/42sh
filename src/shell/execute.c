/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines execute
*/

#include "execute.h"
#include "builtins.h"
#include "../error.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

static void do_child(struct shell *self)
{
    if (self->is_interactive) {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    my_execvp(self->arguments[0], self->arguments);
    my_dputs(self->arguments[0], STDERR_FILENO);
    error(": Command not found.");
    exit(1);
}

static char *get_signal_str(int signal)
{
    if (signal == SIGFPE)
        return "Floating exception";
    if (signal == SIGABRT)
        return "Abort";
    return strsignal(signal);
}

static void do_parent(struct shell *self, pid_t child_pid)
{
    int child_status;

    waitpid(child_pid, &child_status, 0);
    self->last_command_exit_status = WIFEXITED(child_status) ?
        WEXITSTATUS(child_status) : 0;
    if (WIFSIGNALED(child_status))
        my_dprintf(STDERR_FILENO, "%s%s\n",
            get_signal_str(WTERMSIG(child_status)),
            WCOREDUMP(child_status) ? " (core dumped)" : "");
}

void shell_do_line_execute(struct shell *self)
{
    pid_t child_pid;

    if (shell_do_builtins(self))
        return;
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }
    if (child_pid != 0) {
        do_parent(self, child_pid);
        return;
    }
    do_child(self);
}
