/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_character
*/

#pragma once

#include "../../shell.h"
#include "../read_character.h"
#include <stdio.h>

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_lex_get_character(
    struct shell *self, shell_char_t *result)
{
    *result = self->lex.peek_character;

    if (*result != '\0') {
        self->lex.peek_character = 0;
        return true;
    }
    if (!shell_read_character(self, true, result))
        return false;
    if (*result == SHELL_CHAR_ERROR)
        *result = '\n';
    return true;
}

static inline void shell_lex_unget_character(struct shell *self, shell_char_t c)
{
    self->lex.peek_character = c;
}
