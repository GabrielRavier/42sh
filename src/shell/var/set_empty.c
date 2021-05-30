/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_empty
*/

#include "../var.h"

static const shell_char_t NUL = '\0';

bool shell_var_set_empty(struct shell *self, const shell_char_t *var)
{
    return shell_var_set_val_dup(self, var, &NUL, VAR_FLAG_READ_WRITE);
}
