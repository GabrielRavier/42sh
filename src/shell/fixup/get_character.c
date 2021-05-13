/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_character
*/

#include "get_character.h"
#include "read_character.h"

shell_char_t shell_fixup_get_character(struct shell *self)
{
    shell_char_t c = self->fixup.peek_char_get_character;

    if (c != 0) {
        self->fixup.peek_char_get_character = 0;
        return c;
    }
    return shell_fixup_read_character(self);
}
