/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush_child_fds
*/

#include "flush_child_fds.h"
#include "close.h"
#include "open.h"
#include "../fd.h"
#include <unistd.h>
#include <fcntl.h>

void shell_flush_child_fds(struct shell *self)
{
    int fd;

    shell_close(STDIN_FILENO);
    shell_close(STDOUT_FILENO);
    shell_close(STDERR_FILENO);
    self->child_io_fds_setup = false;
    fd = shell_open("/dev/null", O_RDONLY);
    fd_copy(fd, STDOUT_FILENO);
    fd_copy(fd, STDERR_FILENO);
    fd_move(fd, STDIN_FILENO);
}
