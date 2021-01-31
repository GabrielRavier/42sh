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

extern char **environ;

static void do_env(void)
{
    char *const *environ_it = environ;
    while (*environ_it != NULL)
        my_puts(*environ_it++);
}

static bool do_builtins_env(struct shell *self)
{
    if (my_strcmp(self->arguments[0], "env") == 0) {
        do_env();
        return (true);
    }
    if (my_strcmp(self->arguments[0], "setenv") == 0) {
        if (self->arguments[1] == NULL)
            do_env();
        else
            my_setenv(self->arguments[1], self->arguments[2] ?: "", 1);
        return (true);
    }
    if (my_strcmp(self->arguments[0], "unsetenv") == 0) {
        if (self->arguments[1])
            for (char *const *arg_it = &self->arguments[1]; *arg_it; ++arg_it)
                my_unsetenv(*arg_it);
        else
            error("unsetenv: Too few arguments.");
        return (true);
    }
    return (false);
}

static bool do_builtins(struct shell *self)
{
    if (my_strcmp(self->arguments[0], "cd") == 0) {
        if ((self->arguments[1] != NULL || my_getenv("HOME") != NULL) &&
            (chdir(self->arguments[1] ?: my_getenv("HOME")) != 0))
            perror("cd");
        return (true);
    }
    if (my_strcmp(self->arguments[0], "exit") == 0)
        exit(0);
    return (do_builtins_env(self));
}

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

void shell_do_line_execute(struct shell *self)
{
    pid_t child_pid;

    if (do_builtins(self))
        return;
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }
    if (child_pid != 0) {
        waitpid(child_pid, &self->last_child_status, 0);
        return;
    }
    do_child(self);
}
