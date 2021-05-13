/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of get_word
*/

#pragma once

#include "../get_character.h"
#include "../../set_error.h"
#include "../../../shell_char_vector.h"

static inline bool process_char_in_quotes(struct shell *self, shell_char_t *c,
    shell_char_t *quote_char)
{
    if (*c == *quote_char)
        *quote_char = 0;
    else if (*c == '\\') {
        *c = shell_lex_get_character(self);
        if (*c == '\n')
            *c |= SHELL_CHAR_QUOTED;
        shell_lex_unget_character(self, *c);
        *c = '\\' | SHELL_CHAR_QUOTED;
    } else if (*c == '\n') {
        shell_set_error(self, SHELL_ERROR_UNMATCHED_QUOTE, *quote_char);
        shell_lex_unget_character(self, *c);
        return false;
    }
    return true;
}

static inline bool process_special_char(struct shell *self, shell_char_t *c,
    shell_char_t *quote_char)
{
    if (*c == '\\') {
        *c = shell_lex_get_character(self);
        if (*c == '\n')
            return false;
        *c |= SHELL_CHAR_QUOTED;
    } else if (shell_char_is_type(*c, SHELL_CHAR_TYPE_QUOTE))
        *quote_char = *c;
    else {
        shell_lex_unget_character(self, *c);
        return false;
    }
    return true;
}

static inline void part2_letter_loop(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t c)
{
    shell_char_t quote_char = 0;

    while (true) {
        if (quote_char != 0) {
            if (!process_char_in_quotes(self, &c, &quote_char))
                break;
        }
        else if (shell_char_is_type(c, SHELL_CHAR_TYPE_META |
            SHELL_CHAR_TYPE_ESCAPE | SHELL_CHAR_TYPE_QUOTE) &&
            !process_special_char(self, &c, &quote_char))
            break;
        my_shell_char_vector_append_single(word_buffer, c);
        c = shell_lex_get_character(self);
    }
}
