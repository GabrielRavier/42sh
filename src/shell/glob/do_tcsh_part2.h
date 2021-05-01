/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines part 2 of do_tcsh
*/

#pragma once

#include "../glob.h"
#include "../set_error.h"

typedef struct {
    struct shell *self;
    const shell_char_t *home_dir;
    const shell_char_t *username;
    const shell_char_t *str;
    shell_char_t **result;
} ft_opts_t;

static inline bool finish_tilde(ft_opts_t *o)
{
    if (o->home_dir == NULL) {
        if (*o->username != '\0')
            shell_set_error(o->self, SHELL_ERROR_UNKNOWN_USER,
                shell_char_static_xstrdup_to_c(o->username));
        else
            shell_set_error(o->self, SHELL_ERROR_NO_HOME_VAR_SET);
        return false;
    }
    *o->result = (o->home_dir[0] == '/' && o->home_dir[1] == '\0' &&
        o->str[0] == '/') ? shell_char_xstrdup(o->str) :
        shell_char_alloc_concat(o->home_dir, o->str);
    return true;
}
