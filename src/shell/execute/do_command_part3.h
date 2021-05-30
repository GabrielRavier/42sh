/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 3 of do_command
*/

#pragma once

#include "do_command.h"
#include "../fixup.h"
#include "my/string.h"

MY_ATTR_WARN_UNUSED_RESULT static inline bool do_non_paren_pre_fork(
    se_opts_t *o)
{
    if ((o->parse_tree->argv[0][0] & (SHELL_CHAR_QUOTED |
        SHELL_CHAR_NOT_QUOTED)) == SHELL_CHAR_QUOTED)
        my_memmove(o->parse_tree->argv[0], o->parse_tree->argv[0] + 1,
            (shell_char_strlen(o->parse_tree->argv[0] + 1) + 1) * sizeof(
            *o->parse_tree->argv[0]));
    return shell_fixup_parse_tree(o->self, o->parse_tree);
}
