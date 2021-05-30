/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines open
*/

#include "open.h"
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>

int shell_open(const char *pathname, int flags, ...)
{
    mode_t mode = 0;
    va_list arg;
    int result;

    if (flags & O_CREAT) {
        va_start(arg, flags);
        mode = va_arg(arg, mode_t);
        va_end(arg);
    }
    do
        result = open(pathname, flags, mode);
    while (result == -1 && errno == EINTR);
    return result;
}
