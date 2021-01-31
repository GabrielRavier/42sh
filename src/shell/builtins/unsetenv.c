/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin unsetenv
*/

#include "functions.h"
#include "../../error.h"
#include "my/stdlib.h"

void shell_builtin_unsetenv(struct shell *self)
{
    if (self->arguments[1])
        for (char *const *arg_it = &self->arguments[1]; *arg_it; ++arg_it)
            my_unsetenv(*arg_it);
    else
        error("unsetenv: Too few arguments.");
}
