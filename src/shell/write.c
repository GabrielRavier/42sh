/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines write
*/

#include "write.h"
#include <unistd.h>
#include <errno.h>

ssize_t shell_write(int fd, const void *buf, size_t count)
{
    ssize_t result;

    do
        result = write(fd, buf, count);
    while (result == -1 && errno == EINTR);
    return result;
}
