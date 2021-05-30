/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of from_lex_tree_part7
*/

#pragma once

#include "from_lex_tree.h"
#include "../../lexical_word_list.h"
#include "../parse_tree.h"
#include "../set_error.h"
#include "my/cpp-like/algorithm.h"
#include <sys/types.h>

struct parse_part7_state {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    struct shell_parse_tree *parse_tree;
    struct lexical_word_list *i;
    ssize_t argument_count;
    int parens;
    struct lexical_word_list *left_paren_word;
    struct lexical_word_list *right_paren_word;
};

static inline size_t get_argument_count(
    struct parse_part7_state *st)
{
    ssize_t argument_count = 0;

    for (struct lexical_word_list *i = st->word_list; i != st->word_list_end;
        i = i->next)
        switch (i->word[0]) {
            PARSER_SWITCH_PARENS_CASES(st->parens);
        case '>':
        case '<':
            if (st->parens != 0 || i->next == st->word_list_end ||
                shell_char_cstrchr("<>", i->next->word[0]))
                continue;
            --argument_count;
            continue;
        default:
            if (st->parens != 0)
                continue;
            ++argument_count;
            continue;
        }
    return MY_MAX(argument_count, 0);
}

static inline void do_output(struct parse_part7_state *st)
{
    if (st->i->word[1] == '>')
        st->parse_tree->flags |= PARSE_TREE_FLAG_APPEND;
    if (st->i->next == st->word_list_end) {
        shell_set_error(st->self, SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    st->i = st->i->next;
    if (shell_char_cstrchr("<>", st->i->word[0])) {
        shell_set_error(st->self, SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    if ((st->flags & PARSER_FLAGS_PARENS) && (st->parse_tree->flags &
        PARSE_TREE_FLAG_INPUT_HEREDOC))
        shell_set_error(st->self, SHELL_ERROR_CANNOT_HEREDOC_WITHIN_PARENS);
    else if ((st->flags & PARSER_FLAGS_OUTPUT) || st->parse_tree->str_right)
        shell_set_error(st->self, SHELL_ERROR_AMBIGUOUS_OUTPUT_REDIRECT);
    else
        st->parse_tree->str_right = shell_char_xstrdup(st->i->word);
}

static inline void do_input(struct parse_part7_state *st)
{
    if (st->i->word[1] == '<')
        st->parse_tree->flags |= PARSE_TREE_FLAG_INPUT_HEREDOC;
    if (st->i->next == st->word_list_end) {
        shell_set_error(st->self, SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    st->i = st->i->next;
    if (shell_char_cstrchr("<>", st->i->word[0])) {
        shell_set_error(st->self, SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION);
        return;
    }
    if ((st->flags & PARSER_FLAGS_INPUT) || st->parse_tree->str_left)
        shell_set_error(st->self, SHELL_ERROR_AMBIGUOUS_INPUT_REDIRECT);
    else
        st->parse_tree->str_left = shell_char_xstrdup(st->i->word);
}

static inline void do_left_paren(struct parse_part7_state *st)
{
    if (st->parens == 0) {
        if (st->left_paren_word != NULL)
            shell_set_error(st->self, SHELL_ERROR_BADLY_PLACED_LEFT_PAREN);
        st->left_paren_word = st->i->next;
    }
    ++st->parens;
}
