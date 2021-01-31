/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin env
*/

#include "functions.h"
#include "my/stdio.h"
#include <stddef.h>

extern char **environ;

void shell_builtin_env(struct shell *self)
{
    char *const *environ_it = environ;

    (void)self;
    while (*environ_it != NULL)
        my_puts(*environ_it++);
}
