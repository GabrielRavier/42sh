/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush_child_fds
*/

#include "flush_child_fds.h"
#include "../fd.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void shell_flush_child_fds(struct shell *self)
{
    int fd;

    my_close(STDIN_FILENO);
    my_close(STDOUT_FILENO);
    my_close(STDERR_FILENO);
    self->child_io_fds_setup = false;
    fd = my_open("/dev/null", O_RDONLY);
    fd_copy(fd, STDOUT_FILENO);
    fd_copy(fd, STDERR_FILENO);
    fd_move(fd, STDIN_FILENO);
}
