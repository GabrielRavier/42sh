/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares fixup
*/

#pragma once

#include "../shell.h"

// Note: "fixup" here means expanding stuff like quotes and dollars
bool shell_fixup_parse_tree(struct shell *self,
    struct shell_parse_tree *parse_tree) MY_ATTR_WARN_UNUSED_RESULT;
bool shell_fixup_strv(struct shell *self, shell_char_t *const *strv,
    shell_char_t ***result) MY_ATTR_WARN_UNUSED_RESULT;
