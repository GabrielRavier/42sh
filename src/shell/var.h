/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines var
*/

#pragma once

#include "../shell.h"
#include "my/stdlib.h"

// This takes ownership of valv
void shell_var_set_valv(struct shell *self, const shell_char_t *var,
    shell_char_t **valv, int flags);

/// This takes ownership of val
static inline void shell_var_set_val(struct shell *self,
    const shell_char_t *var, shell_char_t *val, int flags)
{
    shell_char_t **valv = my_xmalloc(sizeof(shell_char_t *) * 2);

    valv[0] = val;
    valv[1] = NULL;
    shell_var_set_valv(self, var, valv, flags);
}

static inline void shell_var_set_val_dup(struct shell *self,
    const shell_char_t *var, const shell_char_t *val, int flags)
{
    shell_char_t *copy = shell_char_xstrdup(val);

    shell_var_set_val(self, var, copy, flags);
}

static inline const shell_char_t *shell_var_get_value(struct shell *self,
    const shell_char_t *var)
{
    return var_get_value(&self->vars_head, var);
}
