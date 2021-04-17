/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines move
*/

#include "../fd.h"
#include "my/assert.h"
#include <unistd.h>

int fd_move(int src, int dest)
{
    if (src < 0 || src == dest)
        return src;
    if (dest >= 0) {
        dup2(src, dest);
        if (src != dest)
            close(src);
        return dest;
    }
    dest = fd_copy(src, dest);
    if (dest != src)
        close(src);
    return dest;
}
