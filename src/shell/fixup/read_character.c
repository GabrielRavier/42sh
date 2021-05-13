/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines read_character
*/

#include "read_character.h"

shell_char_t shell_fixup_read_character(struct shell *self)
{
    shell_char_t c = self->fixup.peek_char_read_character;

    if (c != 0) {
        self->fixup.peek_char_read_character = 0;
        return c;
    }
    if (self->fixup.cur_str_input != NULL) {
        c = *self->fixup.cur_str_input++;
        if (c != '\0')
            return c & (SHELL_CHAR_QUOTED | SHELL_CHAR_NOT_QUOTED);
    }
    if (*self->fixup.cur_strv_input == NULL) {
        self->fixup.cur_str_input = NULL;
        return SHELL_CHAR_ERROR;
    }
    self->fixup.cur_str_input = *self->fixup.cur_strv_input++;
    return ' ';
}
