/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Second part of from_lex_tree.c
*/

#pragma once

#include "from_lex_tree.h"
#include "../set_error.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdlib.h"
#include <sys/types.h>
#include <stddef.h>

struct parse_part4_state {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    struct shell_parse_tree *parse_tree;
    struct lexical_word_list *i;
    ssize_t argument_count;
};

static inline size_t parse_part4_get_argument_count(
    struct parse_part4_state *st)
{
    ssize_t argument_count = 0;

    for (struct lexical_word_list *i = st->word_list; i != st->word_list_end;
        i = i->next)
        switch (i->word[0]) {
        case '>':
        case '<':
            if (i->next == st->word_list_end || shell_char_cstrchr("<>",
                i->next->word[0]))
                continue;
            --argument_count;
            continue;
        default:
            ++argument_count;
            continue;
        }
    return MY_MAX(argument_count, 0);
}

static inline void parse_part4_do_output(struct parse_part4_state *st)
{
    if (st->i->word[1] == '>')
        st->parse_tree->flags |= PARSE_TREE_NODE_FLAGS_APPEND;
    if (st->i->next == st->word_list_end) {
        shell_set_error(st->self,
            SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    st->i = st->i->next;
    if (shell_char_cstrchr("<>", st->i->word[0])) {
        shell_set_error(st->self,
            SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    if ((st->flags & PARSER_FLAGS_OUTPUT) || st->parse_tree->str_right)
        shell_set_error(st->self, SHELL_ERROR_AMBIGUOUS_OUTPUT_REDIRECT);
    else
        st->parse_tree->str_right = shell_char_xstrdup(st->i->word);
}

static inline void parse_part4_do_input(struct parse_part4_state *st)
{
    if (st->i->word[1] == '<')
        st->parse_tree->flags |= PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC;
    if (st->i->next == st->word_list_end) {
        shell_set_error(st->self,
            SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    st->i = st->i->next;
    if (shell_char_cstrchr("<>", st->i->word[0])) {
        shell_set_error(st->self,
            SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    if ((st->flags & PARSER_FLAGS_INPUT) || st->parse_tree->str_left)
        shell_set_error(st->self,
            SHELL_ERROR_AMBIGUOUS_INPUT_REDIRECT);
    else
        st->parse_tree->str_left = shell_char_xstrdup(st->i->word);
}

static inline void parse_part4_do_loop(struct parse_part4_state *st)
{
    for (st->i = st->word_list; st->i != st->word_list_end; st->i = st->i->next)
        switch (st->i->word[0]) {
        case '>':
            parse_part4_do_output(st);
            continue;
        case '<':
            parse_part4_do_input(st);
            continue;
        default:
            if (st->self->error == NULL)
                st->parse_tree->argv[st->argument_count++] =
                    shell_char_xstrdup(st->i->word);
            continue;
        }
}

static inline struct shell_parse_tree *parse_part4(struct shell *self,
    struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    struct parse_part4_state st = {self, word_list, word_list_end, flags,
        my_xcalloc(1, sizeof(*st.parse_tree)), NULL, 0};

    st.parse_tree->argv = my_xcalloc(parse_part4_get_argument_count(&st) +
        1, sizeof(st.parse_tree->argv));
    parse_part4_do_loop(&st);
    if (st.argument_count == 0)
        shell_set_error(self, SHELL_ERROR_NULL_COMMAND);
    st.parse_tree->type = PARSE_TREE_NODE_TYPE_COMMAND;
    return st.parse_tree;
}
