/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares get_character
*/

#pragma once

#include "../../shell.h"

shell_char_t shell_fixup_get_character(struct shell *self);

static inline void shell_fixup_unget_character(struct shell *self,
    shell_char_t c)
{
    self->fixup.peek_char_get_character = c;
}
