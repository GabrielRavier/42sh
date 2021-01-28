/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines word
*/

#include "word.h"
#include "../get_character.h"
#include "my/ctype.h"
#include <stdbool.h>

static void do_loop(struct shell *self)
{
    char c;

    while (true) {
        c = shell_get_character(self);
        if (my_isspace(c)) {
            self->peek_character = c;
            *self->line_ptr++ = '\0';
            return;
        }
        *self->line_ptr++ = c;
    }
}

void shell_do_line_word(struct shell *self)
{
    char c;

    *self->arguments_ptr++ = self->line_ptr;
    while (true) {
        c = shell_get_character(self);
        if (my_isspace(c) && c != '\n')
            continue;
        if (c == '\n') {
            *self->line_ptr++ = c;
            *self->line_ptr++ = '\0';
            return;
        }
        break;
    }
    self->peek_character = c;
    do_loop(self);
}
