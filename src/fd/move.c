/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines move
*/

#include "../fd.h"
#include "../shell/close.h"
#include "../shell/dup2.h"

int fd_move(int src, int dest)
{
    if (src < 0 || src == dest)
        return src;
    if (dest >= 0) {
        shell_dup2(src, dest);
        if (src != dest)
            shell_close(src);
        return dest;
    }
    dest = fd_copy(src, dest);
    if (dest != src)
        shell_close(src);
    return dest;
}
