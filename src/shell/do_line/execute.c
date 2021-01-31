/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines execute
*/

#include "execute.h"
#include "../../error.h"
#include "my/stdio.h"
#include "my/string.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static bool do_builtins(struct shell *self)
{
    if (my_strcmp(self->arguments[0], "cd") == 0) {
        if ((self->arguments[1] || my_getenv("HOME")) &&
            (chdir(self->arguments[1] ?: my_getenv("HOME")) != 0))
            perror("cd");
        return (true);
    }
    if (my_strcmp(self->arguments[0], "exit") == 0)
        exit(0);
    return (false);
}

void shell_do_line_execute(struct shell *self)
{
    pid_t child_pid;
    int child_status;

    if (do_builtins(self))
        return;
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }
    if (child_pid != 0) {
        waitpid(child_pid, &child_status, 0);
        return;
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    my_execvp(self->arguments[0], self->arguments);
    my_dputs(self->arguments[0], STDERR_FILENO);
    error(": Command not found.");
    exit(1);
}
