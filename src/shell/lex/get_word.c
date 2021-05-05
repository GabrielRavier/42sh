/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_word
*/

#include "get_word.h"
#include "get_character.h"
#include "../../shell_char_vector.h"

static shell_char_t *finish_buffer(struct my_shell_char_vector *word_buffer)
{
    my_shell_char_vector_append_single(word_buffer, 0);
    return my_shell_char_vector_move_buffer(word_buffer);
}

static bool do_meta_characters(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t *c)
{
    shell_char_t c_after;

    if (*c == '<' || *c == '>') {
        my_shell_char_vector_append_single(word_buffer, *c);
        c_after = shell_lex_get_character(self);
        if (c_after == *c)
            my_shell_char_vector_append_single(word_buffer, c_after);
        else
            shell_lex_unget_character(self, c_after);
        return false;
    }
    if (*c == '|' || *c == ';' || *c == '\n') {
        my_shell_char_vector_append_single(word_buffer, *c);
        return false;
    }
    return true;
}

// If this returns false, the caller should immediately return (the word is
// over)
static bool get_first_char(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t *c)
{
    while (true) {
        do
            *c = shell_lex_get_character(self);
        while (*c == ' ' || *c == '\t');
        if (!do_meta_characters(self, word_buffer, c))
            return false;
        if (*c == '\\') {
            *c = shell_lex_get_character(self);
            if (*c == '\n')
                continue;
            *c |= SHELL_CHAR_QUOTE;
        }
        return true;
    }
}

static void letter_loop(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t c)
{
    while (true) {
        if (shell_char_is_type(c, SHELL_CHAR_TYPE_META |
            SHELL_CHAR_TYPE_ESCAPE)) {
            if (c == '\\') {
                c = shell_lex_get_character(self);
                if (c == '\n')
                    break;
                c |= SHELL_CHAR_QUOTE;
            } else {
                shell_lex_unget_character(self, c);
                break;
            }
        }
        my_shell_char_vector_append_single(word_buffer, c);
        c = shell_lex_get_character(self);
    }
}

shell_char_t *shell_lex_get_word(struct shell *self)
{
    shell_char_t c;
    struct my_shell_char_vector *word_buffer = my_shell_char_vector_new();

    if (!get_first_char(self, word_buffer, &c))
        return finish_buffer(word_buffer);
    letter_loop(self, word_buffer, c);
    return finish_buffer(word_buffer);
}
