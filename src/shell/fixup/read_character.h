/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines read_character
*/

#pragma once

#include "../../shell.h"

shell_char_t shell_fixup_read_character(struct shell *self);

static inline void shell_fixup_unread_character(struct shell *self,
    shell_char_t c)
{
    self->fixup.peek_char_read_character = c;
}
