/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtins stuff
*/

#include "builtins.h"
#include "builtins/functions.h"
#include "../error.h"
#include "my/cpp-like/iterator.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <stddef.h>

static const struct builtin_func {
    const char *name;
    void (*func)(struct shell *self);
} BUILTINS[] = {
    {"env", shell_builtin_env},
    {"setenv", shell_builtin_setenv},
    {"unsetenv", shell_builtin_unsetenv},
    {"cd", shell_builtin_cd},
    {"exit", shell_builtin_exit}
};

bool shell_do_builtins(struct shell *self)
{
    for (size_t i = 0; i < MY_ARRAY_SIZE(BUILTINS); ++i)
        if (my_strcmp(self->arguments[0], BUILTINS[i].name) == 0) {
            BUILTINS[i].func(self);
            return (true);
        }
    return (false);
}
