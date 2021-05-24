/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of str
*/

#pragma once

#include "../glob.h"
#include "../set_error.h"
#include "../../shell_char.h"
#include "my/assert.h"
#include "my/stdlib.h"

static const shell_char_t NUL = '\0';

typedef struct {
    struct shell *self;
    const shell_char_t *str;
    shell_char_t **tmp_strv;
    int flags;
    shell_char_t **result;
} hmto_opts_t;

static inline bool do_append(hmto_opts_t *o)
{
    size_t total_chars_in_strv = 0;
    size_t i = 0;

    for (shell_char_t **i = o->tmp_strv; *i != NULL; ++i)
        total_chars_in_strv += shell_char_strlen(*i) + 1;
    o->result = my_xmalloc(total_chars_in_strv * sizeof(*o->result));
    i = 0;
    for (shell_char_t **j = o->tmp_strv; *j != NULL; ++j) {
        for (size_t k = 0; (*j)[k] != '\0'; ++k)
            (*o->result)[i++] = (*j)[k] & SHELL_CHAR_NOT_QUOTED;
        (*o->result)[i++] = j[1] == NULL ? '\0' : ' ';
    }
    shell_char_strv_free(o->tmp_strv);
    return true;
}

static inline bool handle_more_than_one(hmto_opts_t *o)
{
    switch (o->flags) {
    case SHELL_GLOB_STR_FLAG_ERROR:
        o->self->error_program_name = shell_char_static_xstrdup_to_c(o->str);
        shell_char_strv_free(o->tmp_strv);
        shell_set_error(o->self, SHELL_ERROR_FLAG_NAME | SHELL_ERROR_AMBIGUOUS);
        return false;
    case SHELL_GLOB_STR_FLAG_APPEND:
        return do_append(o);
    default:
        MY_ASSERT(false && "Should never be reached");
    }
}

typedef struct {
    struct shell *self;
    const shell_char_t *str;
    int flags;
    shell_char_t **result_strv;
    shell_char_t **result;
} mr_opts_t;

static inline bool make_result(mr_opts_t *o)
{
    if (o->result_strv != NULL && o->result_strv[0] == NULL) {
        my_free(o->result_strv);
        *o->result = shell_char_xstrdup(&NUL);
        return true;
    }
    if (o->result_strv[1] != NULL)
        return handle_more_than_one(&((hmto_opts_t){o->self, o->str,
            o->result_strv, o->flags, o->result}));
    *o->result = shell_char_str_unquote(*o->result_strv);
    my_free(o->result_strv);
    return true;
}
