/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 3 of strv
*/

#pragma once

#include "get_character.h"
#include "read_character.h"
#include "../set_error.h"
#include "../../shell_char_ptr_vector.h"
#include "../../shell_char_vector.h"
#include <stdbool.h>

static inline bool do_word_end(struct my_shell_char_ptr_vector *fixup_result,
    struct my_shell_char_vector *word_buffer, bool *result)
{
    my_shell_char_vector_append_single(word_buffer, '\0');
    my_shell_char_ptr_vector_append_single(fixup_result,
        my_shell_char_vector_move_buffer(word_buffer));
    *result = true;
    return true;
}

static inline bool do_word_fail_cleanup(
    struct my_shell_char_vector *word_buffer)
{
    my_shell_char_vector_free(word_buffer);
    return false;
}

static inline bool do_word_pack_handle_backslash(struct shell *self,
    shell_char_t *c)
{
    if (*c == '\\') {
        *c = shell_fixup_get_character(self);
        if (*c == SHELL_CHAR_ERROR) {
            shell_fixup_unread_character(self, *c);
            return true;
        }
        if (*c == '\n')
            *c = ' ';
        else
            *c |= SHELL_CHAR_QUOTED;
    }
    return false;
}

static inline bool do_word_pack(struct shell *self,
    struct my_shell_char_vector *word_buffer)
{
    shell_char_t c;

    while (true) {
        c = shell_fixup_get_character(self);
        if (do_word_pack_handle_backslash(self, &c))
            return true;
        if (c == SHELL_CHAR_ERROR) {
            shell_fixup_unread_character(self, c);
            return true;
        }
        if (shell_char_is_type(c, SHELL_CHAR_TYPE_SPACE |
            SHELL_CHAR_TYPE_NEWLINE | SHELL_CHAR_TYPE_QUOTE)) {
            shell_fixup_unget_character(self, c);
            return !shell_char_is_type(c, SHELL_CHAR_TYPE_ALL_QUOTES);
        }
        my_shell_char_vector_append_single(word_buffer, c);
    }
}

// All further interpretation of characters between ' is left alone for later
static inline bool do_word_quoted_char_loop(struct shell *self,
    struct my_shell_char_vector *word_buffer, shell_char_t quoted_char)
{
    shell_char_t c;

    while (true) {
        c = shell_fixup_get_character(self);
        if (c == quoted_char)
            break;
        if (c == '\n' || c == SHELL_CHAR_ERROR) {
            shell_set_error(self, SHELL_ERROR_UNMATCHED_QUOTE, quoted_char);
            return false;
        }
        if (((c & (SHELL_CHAR_QUOTED | SHELL_CHAR_NOT_QUOTED)) ==
            ('\n' | SHELL_CHAR_QUOTED)) && (word_buffer->size != 0 &&
            (word_buffer->data[word_buffer->size - 1] &
            SHELL_CHAR_NOT_QUOTED) == '\\'))
            my_shell_char_vector_resize(word_buffer, word_buffer->size - 1);
        my_shell_char_vector_append_single(word_buffer, c | SHELL_CHAR_QUOTED);
    }
    return true;
}
