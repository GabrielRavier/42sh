/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_all
*/

#include "../glob.h"
#include "../../shell_char.h"

bool shell_glob_strv_all(struct shell *self,
    const shell_char_t **strv, int flags, shell_char_t ***result)
{
    if (strv == NULL || strv[0] == NULL) {
        *result = shell_char_strv_dup(strv);
        return true;
    }
    if (flags & SHELL_GLOB_FLAG_TCSH) {
        if (!shell_glob_do_tc_sh(self, strv, result))
            return false;
    } else
        *result = shell_char_strv_dup(strv);
    shell_char_strv_unquote(*result);
    return true;
}
