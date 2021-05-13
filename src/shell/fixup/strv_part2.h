/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of strv
*/

#pragma once

#include "strv_part3.h"

struct do_word_state {
    struct my_shell_char_vector *word_buffer;
    shell_char_t c;
    shell_char_t quoted_char;
    bool has_done_char;
    int iter_result;
    bool *result;
};

static inline bool do_error_or_newline(struct shell *self,
    const struct do_word_state *st)
{
    if (st->c == SHELL_CHAR_ERROR)
        if (st->has_done_char == false) {
            my_shell_char_vector_free(st->word_buffer);
            *st->result = false;
            return false;
        }
    shell_fixup_unread_character(self, st->c);
    return true;
}

static inline bool do_word_loop_iter_backslash(struct shell *self,
    struct do_word_state *st)
{
    st->c = shell_fixup_get_character(self);
    if (st->c == '\n' || st->c == SHELL_CHAR_ERROR)
        return false;
    st->c |= SHELL_CHAR_QUOTED;
    return true;
}

// See do_word_loop_iter for information on return values from here
static inline int do_word_loop_iter_quote(struct shell *self,
    struct do_word_state *st)
{
    st->quoted_char = st->c;
    if (!do_word_quoted_char_loop(self, st->word_buffer, st->quoted_char))
        return 3;
    st->has_done_char = true;
    return do_word_pack(self, st->word_buffer) ? 2 : 0;
}

// return values:
// 0 means continue as normal
// 1 means return true
// 2 means do end
// 3 means do fail cleanup
static inline int do_word_loop_iter(struct shell *
    self, struct do_word_state *st)
{
    st->c = shell_fixup_get_character(self);
    switch (st->c) {
    case ' ':
    case '\t':
    case SHELL_CHAR_ERROR:
    case '\n':
        return st->c == ' ' || st->c == '\t' ? 0 : 1 + do_error_or_newline(self,
            st);
    case '\'':
    case '"':
        return do_word_loop_iter_quote(self, st);
    case '\\':
        if (!do_word_loop_iter_backslash(self, st))
            return 0;
    }
    shell_fixup_unget_character(self, st->c);
    st->has_done_char = true;
    return do_word_pack(self, st->word_buffer) ? 2 : 0;
}

// Analogous to shell_lex_get_word, but for fixing up stuff lol
static inline bool do_word(struct shell *self,
    struct my_shell_char_ptr_vector *fixup_result, bool *result)
{
    struct do_word_state st = {.word_buffer = my_shell_char_vector_new(),
        .result = result};
    int iter_result;

    while (true) {
        iter_result = do_word_loop_iter(self, &st);
        if (iter_result == 1)
            return true;
        if (iter_result == 2)
            return do_word_end(fixup_result, st.word_buffer, result);
        if (iter_result == 3)
            return do_word_fail_cleanup(st.word_buffer);
    }
}
