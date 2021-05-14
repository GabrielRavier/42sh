/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines fds
*/

#include "../init.h"
#include "../../fd.h"
#include <unistd.h>
#include <fcntl.h>

static void do_one(int *result, int src, int dest)
{
    *result = fd_copy(src, dest);
    fcntl(*result, F_SETFD, FD_CLOEXEC);
}

void shell_init_fds(struct shell *self)
{
    self->child_io_fds_setup = false;
    do_one(&self->input_fd, STDIN_FILENO, SHELL_PREFERRED_INPUT_FD);
    do_one(&self->output_fd, STDOUT_FILENO, SHELL_PREFERRED_OUTPUT_FD);
    do_one(&self->error_output_fd, STDERR_FILENO,
        SHELL_PREFERRED_ERROR_OUTPUT_FD);
    do_one(&self->old_stdin_fd, self->input_fd, SHELL_PREFERRED_OLD_STDIN_FD);
}
