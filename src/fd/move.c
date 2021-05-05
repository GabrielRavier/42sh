/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines move
*/

#include "../fd.h"
#include "my/unistd.h"
#include <unistd.h>

int fd_move(int src, int dest)
{
    if (src < 0 || src == dest)
        return src;
    if (dest >= 0) {
        dup2(src, dest);
        if (src != dest)
            my_close(src);
        return dest;
    }
    dest = fd_copy(src, dest);
    if (dest != src)
        my_close(src);
    return dest;
}
