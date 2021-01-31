/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin unsetenv
*/

#include "functions.h"
#include "../../error.h"
#include "my/stdlib.h"
#include <stdio.h>

int shell_builtin_unsetenv(struct shell *self)
{
    if (self->arguments[1]) {
        for (char *const *arg_it = &self->arguments[1]; *arg_it; ++arg_it)
            if (my_unsetenv(*arg_it) < 0) {
                perror("unsetenv");
                return (1);
            }
    } else {
        error("unsetenv: Too few arguments.");
        return (1);
    }
    return (0);
}
