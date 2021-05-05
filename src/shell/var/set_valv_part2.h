/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines part 2 of set_valv
*/

#pragma once

#include "../../shell_char.h"
#include "../../var.h"
#include <stdbool.h>

struct dl_opts_t {
    const shell_char_t *var;
    shell_char_t **valv;
    int flags;
    int *strcmp_result;
    struct var **var_i;
};

static bool do_loop(struct dl_opts_t *o)
{
    struct var *var_j;

    while ((*o->var_i)->links[*o->strcmp_result] != NULL) {
        var_j = (*o->var_i)->links[*o->strcmp_result];
        *o->strcmp_result = shell_char_strcmp(o->var, var_j->name);
        if (*o->strcmp_result == 0) {
            shell_char_strv_free(var_j->valv);
            var_j->flags = o->flags;
            var_j->valv = o->valv;
            shell_char_strv_unquote(var_j->valv);
            return true;
        }
        *o->var_i = var_j;
        *o->strcmp_result = *o->strcmp_result > 0;
    }
    return false;
}
