/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines creat
*/

#include "creat.h"
#include <fcntl.h>
#include <errno.h>

int shell_creat(const char *pathname, mode_t mode)
{
    int result;

    do
        result = creat(pathname, mode);
    while (result == -1 && errno == EINTR);
    return result;
}
