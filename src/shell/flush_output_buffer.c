/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush_output_buffer
*/

#include "flush_output_buffer.h"
#include "exit.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include <stdlib.h>
#include <unistd.h>

void shell_flush_output_buffer(struct shell *self)
{
    int fd;

    if (self->line_buffer == self->line_buffer_current_ptr)
        return;
    fd = self->handling_error ? (self->child_io_fds_setup ? STDERR_FILENO :
        self->error_output_fd) : (self->child_io_fds_setup ? STDOUT_FILENO :
        self->output_fd);
    if (my_write(fd, self->line_buffer, self->line_buffer_current_ptr -
        self->line_buffer) == -1) {
        my_dputs("Failed to flush output buffer\n", STDERR_FILENO);
        my_dputs("Failed to flush output buffer\n", self->error_output_fd);
        shell_exit(self, 1);
    }
    self->line_buffer_current_ptr = self->line_buffer;
}
