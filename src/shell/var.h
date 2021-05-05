/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines var
*/

#pragma once

#include "../shell.h"
#include "my/stdlib.h"
#include "my/features.h"

// This takes ownership of valv
bool shell_var_set_valv(struct shell *self, const shell_char_t *var,
    shell_char_t **valv, int flags) MY_ATTR_WARN_UNUSED_RESULT;

/// This takes ownership of val
MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_var_set_val(
    struct shell *self, const shell_char_t *var, shell_char_t *val, int flags)
{
    shell_char_t **valv = my_xmalloc(sizeof(shell_char_t *) * 2);

    valv[0] = val;
    valv[1] = NULL;
    return shell_var_set_valv(self, var, valv, flags);
}

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_var_set_val_dup(
    struct shell *self, const shell_char_t *var, const shell_char_t *val,
    int flags)
{
    shell_char_t *copy = shell_char_xstrdup(val);

    return shell_var_set_val(self, var, copy, flags);
}

MY_ATTR_WARN_UNUSED_RESULT static inline const struct var *shell_var_get(
    struct shell *self, const shell_char_t *var)
{
    return var_get(&self->vars_head, var);
}

MY_ATTR_WARN_UNUSED_RESULT static inline const shell_char_t *
    shell_var_get_value(struct shell *self, const shell_char_t *var)
{
    return var_get_value(&self->vars_head, var);
}
