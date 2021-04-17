/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines fds
*/

#include "../init.h"
#include "../../fd.h"
#include <unistd.h>

void shell_init_fds(struct shell *self)
{
    self->child_io_fds_setup = false;
    self->input_fd = fd_copy(STDIN_FILENO, SHELL_PREFERRED_INPUT_FD);
    self->output_fd = fd_copy(STDOUT_FILENO, SHELL_PREFERRED_OUTPUT_FD);
    self->error_output_fd = fd_copy(STDERR_FILENO,
        SHELL_PREFERRED_ERROR_OUTPUT_FD);
    self->old_stdin_fd = fd_copy(self->input_fd,
        SHELL_PREFERRED_OLD_STDIN_FD);
}
