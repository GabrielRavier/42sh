/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines str
*/

#include "../glob.h"
#include "str_part2.h"
#include "../get_home_dir.h"
#include "../set_error.h"
#include "my/assert.h"
#include "my/stdlib.h"

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
        return (!shell_glob_do_tc_sh(self, strv, &tmp_strv)) ? false :
            make_result(&((mr_opts_t){self, str, flags, tmp_strv, result}));
    __builtin_trap();
}
