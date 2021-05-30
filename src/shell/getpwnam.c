/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines getpwnam
*/

#include "getpwnam.h"
#include <errno.h>
#include <stddef.h>
#include <stdbool.h>

struct passwd *shell_getpwnam(const char *name)
{
    struct passwd *result;

    do {
        errno = 0;
        result = getpwnam(name);
    } while (result == NULL && errno == EINTR);
    return result;
}
