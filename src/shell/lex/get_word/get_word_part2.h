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

MY_ATTR_WARN_UNUSED_RESULT static inline bool process_char_in_quotes(
    struct shell *self, shell_char_t *c, shell_char_t *quote_char, bool *result)
{
    if (*c == *quote_char)
        *quote_char = 0;
    else if (*c == '\\') {
        if (!shell_lex_get_character(self, c))
            return false;
        if (*c == '\n')
            *c |= SHELL_CHAR_QUOTED;
        shell_lex_unget_character(self, *c);
        *c = '\\' | SHELL_CHAR_QUOTED;
    } else if (*c == '\n') {
        shell_set_error(self, SHELL_ERROR_UNMATCHED_QUOTE, *quote_char);
        shell_lex_unget_character(self, *c);
        *result = false;
        return true;
    }
    *result = true;
    return true;
}

MY_ATTR_WARN_UNUSED_RESULT static inline bool process_special_char(
    struct shell *self, shell_char_t *c, shell_char_t *quote_char, bool *result)
{
    if (*c == '\\') {
        if (!shell_lex_get_character(self, c))
            return false;
        if (*c == '\n') {
            *result = false;
            return true;
        }
        *c |= SHELL_CHAR_QUOTED;
    } else if (shell_char_is_type(*c, SHELL_CHAR_TYPE_QUOTE))
        *quote_char = *c;
    else {
        shell_lex_unget_character(self, *c);
        *result = false;
        return true;
    }
    *result = true;
    return true;
}

// If this returns 0, all is fine
// If this returns 1, return false
// If this returns 2, break
MY_ATTR_WARN_UNUSED_RESULT static inline int part2_letter_loop_do_it(
    struct shell *self, struct my_shell_char_vector *word_buffer,
    shell_char_t *quote_char, shell_char_t *c)
{
    bool should_continue;

    if (*quote_char != 0) {
        if (!process_char_in_quotes(self, c, quote_char, &should_continue))
            return 1;
        if (!should_continue)
            return 2;
    }
    else if (shell_char_is_type(*c, SHELL_CHAR_TYPE_META |
        SHELL_CHAR_TYPE_ESCAPE | SHELL_CHAR_TYPE_QUOTE)) {
        if (!process_special_char(self, c, quote_char, &should_continue))
            return 1;
        if (!should_continue)
            return 2;
    }
    my_shell_char_vector_append_single(word_buffer, *c);
    return !shell_lex_get_character(self, c) ? 1 : 0;
}

MY_ATTR_WARN_UNUSED_RESULT static inline bool part2_letter_loop(
    struct shell *self, struct my_shell_char_vector *word_buffer,
    shell_char_t c)
{
    shell_char_t quote_char = 0;
    int loop_it_decision;

    do {
        loop_it_decision = part2_letter_loop_do_it(self, word_buffer,
            &quote_char, &c);
        if (loop_it_decision == 1)
            return false;
    } while (loop_it_decision != 2);
    return true;
}
