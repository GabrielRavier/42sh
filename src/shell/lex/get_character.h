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

static inline shell_char_t shell_lex_get_character(struct shell *self)
{
    shell_char_t c = self->lex.peek_character;
    if (c != 0) {
        self->lex.peek_character = 0;
        return c;
    }
    c = shell_read_character(self, true);
    return c == SHELL_CHAR_ERROR ? '\n' : c;
}

static inline void shell_lex_unget_character(struct shell *self, shell_char_t c)
{
    self->lex.peek_character = c;
}
