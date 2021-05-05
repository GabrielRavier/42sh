/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines fork
*/

#include "fork.h"
#include "set_error.h"
#include "print_error.h"
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pid_t shell_fork(struct shell *self, struct shell_parse_tree *parse_tree)
{
    pid_t pid = fork();
    if (pid == -1) {
        shell_set_error(self, SHELL_ERROR_NO_MORE_PROCESSES);
        shell_print_error(self);
    }
    if (pid == 0) {
        ++self->child_depth;
        if (self->should_set_interrupts) {
            self->should_set_interrupts = false;
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
        }
    } else
        shell_proc_add(self, pid, parse_tree);
    return pid;
}
