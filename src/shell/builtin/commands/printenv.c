/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin printenv
*/

#include "../commands.h"
#include "my/stdio.h"
#include <stddef.h>

extern char **environ;

void shell_builtin_printenv(struct shell *shell, shell_char_t **argv)
{
    char *const *environ_it = environ;

    (void)shell;
    (void)argv;
    while (*environ_it != NULL)
        my_puts(*environ_it++);
    return;
}
