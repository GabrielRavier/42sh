/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines copy
*/

#include "../fd.h"
#include "../shell.h"
#include <unistd.h>

static int recursively_use_fds(int src, int dest)
{
    int tmp = dup(src);

    if (tmp < 0)
        return -1;
    if (dest == -1 && tmp > SHELL_SAFE_FD)
        return tmp;
    if (tmp != dest) {
        dest = recursively_use_fds(tmp, dest);
        close(tmp);
        return dest;
    }
    return tmp;
}

int fd_copy(int src, int dest)
{
    if (src == dest || src < 0 || (dest < 0 && src > SHELL_SAFE_FD))
        return src;
    if (dest >= 0) {
        dup2(src, dest);
        return dest;
    }
    return recursively_use_fds(src, dest);
}
