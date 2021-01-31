/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin setenv
*/

#include "functions.h"
#include "../../error.h"
#include "my/stdlib.h"
#include "my/ctype.h"
#include <stdio.h>
#include <stddef.h>

void shell_builtin_setenv(struct shell *self)
{
    if (self->arguments[1] == NULL) {
        shell_builtin_env(self);
        return;
    }
    if (!my_isalpha(self->arguments[1][0])) {
        error("setenv: Variable name must begin with a letter.");
        return;
    }
    for (size_t i = 0; self->arguments[1][i]; ++i)
        if (!my_isalnum(self->arguments[1][i]) &&
            self->arguments[1][i] != '_') {
            error(
                "setenv: Variable name must contain alphanumeric characters.");
            return;
        }
    if (my_setenv(self->arguments[1], self->arguments[2] ?: "", 1) < 0)
        perror("setenv");
}
