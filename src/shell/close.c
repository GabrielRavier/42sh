/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines close
*/

#include "close.h"
#include <unistd.h>
#include <errno.h>

void shell_close(int fd)
{
    if (fd < 0)
        return;
    while (close(fd) == -1 && errno == EINTR);
}
