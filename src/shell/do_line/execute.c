/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines execute
*/

#include "execute.h"
#include "../../error.h"
#include "my/string.h"
#include "my/stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

static void do_exec(struct shell *self)
{
    char *path;

    if (my_asprintf(&path, "%s/%s", "/bin", self->arguments[0]) < 0)
        return;
    execve(path, self->arguments, environ);
    my_dputs(self->arguments[0], STDERR_FILENO);
    error(": not found");
    exit(1);
}

static bool do_builtins(struct shell *self)
{
    if (my_strcmp(self->arguments[0], "cd") == 0) {
        if (self->arguments[1]) {
            if (chdir(self->arguments[1]) != 0)
                perror("cd");
        } else
            error("cd: Argument count");
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
    do_exec(self);
}
