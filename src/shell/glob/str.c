/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines str
*/

#include "../glob.h"
#include "../get_home_dir.h"
#include "../set_error.h"
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

static bool handle_more_than_one(hmto_opts_t *o)
{
    MY_ASSERT(o->flags == SHELL_GLOB_STR_FLAG_ERROR);
    o->self->error_program_name = shell_char_static_xstrdup_to_c(o->str);
    shell_char_strv_free(o->tmp_strv);
    shell_set_error(o->self, SHELL_ERROR_FLAG_NAME | SHELL_ERROR_AMBIGUOUS);
    return false;
}

typedef struct {
    struct shell *self;
    const shell_char_t *str;
    int flags;
    shell_char_t **result_strv;
    shell_char_t **result;
} mr_opts_t;

static bool make_result(mr_opts_t *o)
{
    if (o->result_strv != NULL && o->result_strv[0] == NULL) {
        my_free(o->result_strv);
        *o->result = shell_char_xstrdup(&NUL);
        return true;
    }
    if (o->result_strv[1])
        return handle_more_than_one(&((hmto_opts_t){o->self, o->str,
            o->result_strv, o->flags, o->result}));
    *o->result = shell_char_str_unquote(*o->result_strv);
    my_free(o->result_strv);
    return true;
}

bool shell_glob_str(struct shell *self, const shell_char_t *str, int flags,
    shell_char_t **result)
{
    const shell_char_t *strv[2] = {str, NULL};
    int glob_flags = shell_glob_strv_get_flags(strv);
    shell_char_t **tmp_strv;

    if (glob_flags == SHELL_GLOB_FLAG_NONE) {
        *result = shell_char_str_unquote(shell_char_xstrdup(str));
        return true;
    }
    if (glob_flags & SHELL_GLOB_FLAG_TCSH)
        return (!shell_glob_do_tcsh(self, strv, &tmp_strv)) ? false :
            make_result(&((mr_opts_t){self, str, flags, tmp_strv, result}));
    __builtin_trap();
}
