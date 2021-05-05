/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines copy
*/

#include "../fd.h"
#include "../shell.h"
#include "my/unistd.h"
#include <unistd.h>

static int recursively_use_fds_until_dest(int src, int dest)
{
    int new_fd = dup(src);

    if (new_fd < 0)
        return -1;
    if (dest == -1 && new_fd > SHELL_SAFE_FD)
        return new_fd;
    if (new_fd != dest) {
        dest = recursively_use_fds_until_dest(new_fd, dest);
        my_close(new_fd);
        return dest;
    }
    return new_fd;
}

int fd_copy(int src, int dest)
{
    if (src == dest || src < 0 || (dest < 0 && src > SHELL_SAFE_FD))
        return src;
    if (dest >= 0) {
        dup2(src, dest);
        return dest;
    }
    return recursively_use_fds_until_dest(src, dest);
}
