/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines setenv
*/

#include "setenv.h"
#include "my/stdlib.h"
#include <stdlib.h>

void shell_setenv(const shell_char_t *name, const shell_char_t *value)
{
    char *name_as_c = shell_char_xstrdup_to_c(name);

    setenv(name_as_c, shell_char_static_xstrdup_to_c(value), 1);
    my_free(name_as_c);
}
