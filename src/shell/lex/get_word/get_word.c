/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_word
*/

#include "../get_word.h"
#include "../get_character.h"
#include "get_word_part2.h"
#include "../../../shell_char_vector.h"

static shell_char_t *finish_buffer(struct my_shell_char_vector *word_buffer)
{
    my_shell_char_vector_append_single(word_buffer, 0);
    return my_shell_char_vector_move_buffer(word_buffer);
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_meta_characters(struct shell *self,
    struct my_shell_char_vector *word_buffer, const shell_char_t * c,
    bool *result)
{
    shell_char_t c_after;

    if (*c == '<' || *c == '>' || *c == '&' || *c == '|') {
        my_shell_char_vector_append_single(word_buffer, *c);
        if (!shell_lex_get_character(self, &c_after))
            return false;
        if (c_after == *c)
            my_shell_char_vector_append_single(word_buffer, c_after);
        else
            shell_lex_unget_character(self, c_after);
        *result = false;
        return true;
    }
    if (*c == ';' || *c == '\n') {
        my_shell_char_vector_append_single(word_buffer, *c);
        *result = false;
        return true;
    }
    *result = true;
    return true;
}

MY_ATTR_WARN_UNUSED_RESULT static bool
    get_first_char_do_loop_and_meta_characters(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t *c,
    bool *do_meta_characters_result)
{
    do
        if (!shell_lex_get_character(self, c))
            return false;
    while (*c == ' ' || *c == '\t');
    return do_meta_characters(self, word_buffer, c, do_meta_characters_result);
}

// If *result is false after this, the caller should immediately return (the
// word is over)
MY_ATTR_WARN_UNUSED_RESULT static bool get_first_char(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t *c, bool *result)
{
    bool do_meta_characters_result;

    while (true) {
        if (!get_first_char_do_loop_and_meta_characters(self, word_buffer, c,
            &do_meta_characters_result))
            return false;
        if (!do_meta_characters_result) {
            *result = false;
            return true;
        }
        if (*c == '\\') {
            if (!shell_lex_get_character(self, c))
                return false;
            if (*c == '\n')
                continue;
            *c |= SHELL_CHAR_QUOTED;
        }
        *result = true;
        return true;
    }
}

bool shell_lex_get_word(struct shell *self, shell_char_t **result)
{
    shell_char_t c;
    struct my_shell_char_vector *word_buffer = my_shell_char_vector_new();
    bool should_do_letter_loop;

    if (!get_first_char(self, word_buffer, &c, &should_do_letter_loop) ||
        (should_do_letter_loop && !part2_letter_loop(self, word_buffer, c))) {
        my_shell_char_vector_free(word_buffer);
        return false;
    }
    *result = finish_buffer(word_buffer);
    return true;
}
