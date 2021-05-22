/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines pipe
*/

#include "pipe.h"
#include "set_and_print_error.h"
#include "../fd.h"
#include <unistd.h>
#include <fcntl.h>

static void cant_make_pipe(struct shell *self)
{
    ++self->child_depth;
    shell_set_and_print_error(self, SHELL_ERROR_CANT_MAKE_PIPE);
}

// TODO Add proper error handling here instead of forcing an exit
void shell_pipe(struct shell *self, int pipefd[2])
{
    if (pipe(pipefd) < 0)
        cant_make_pipe(self);
    for (size_t i = 0; i <= 1; ++i) {
        pipefd[i] = fd_move(pipefd[i], -1);
        fcntl(pipefd[i], F_SETFD, FD_CLOEXEC);
    }
    if (pipefd[0] >= 0 && pipefd[1] >= 0)
        return;
    for (size_t i = 0; i <= 1; ++i)
        if (pipefd[i] >= 0)
            close(pipefd[i]);
    cant_make_pipe(self);
}
