/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines dup2
*/

#include "dup2.h"
#include <unistd.h>
#include <errno.h>

int shell_dup2(int oldfd, int newfd)
{
    int result;

    do
        result = dup2(oldfd, newfd);
    while (result == -1 && errno == EINTR);
    return result;
}
