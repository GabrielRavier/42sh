/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of from_lex_tree_part2
*/

#pragma once

#include "from_lex_tree_part3.h"
#include "../parse_tree.h"
#include "../set_error.h"
#include "my/stdlib.h"

typedef struct {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    struct lexical_word_list *i;
} da_opts_t;

typedef struct {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    int parens;
} f_opts_t;

typedef struct {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    int *parens;
    struct lexical_word_list **i;
    struct shell_parse_tree **result;
} dli_opts_t;

static inline struct shell_parse_tree *do_ampersand_finish(dli_opts_t *o,
    struct shell_parse_tree *intermediate)
{
    struct shell_parse_tree *result = my_xcalloc(1, sizeof(*result));

    result->type = PARSE_TREE_TYPE_LIST;
    result->node_left = intermediate;
    result->node_right = shell_parse_tree_from_lex_tree(o->self, *o->i,
        o->word_list_end, o->flags);
    return result;
}

static inline struct shell_parse_tree *do_ampersand(dli_opts_t *o)
{
    struct shell_parse_tree *intermediate =
        shell_parse_tree_from_lex_tree_part3(o->self, o->word_list, *o->i,
        o->flags);
    struct shell_parse_tree *tmp_parens;

    if (intermediate->type == PARSE_TREE_TYPE_LIST ||
        intermediate->type == PARSE_TREE_TYPE_AND ||
        intermediate->type == PARSE_TREE_TYPE_OR) {
        tmp_parens = my_xcalloc(1, sizeof(*tmp_parens));
        tmp_parens->type = PARSE_TREE_TYPE_PARENS;
        tmp_parens->flags = PARSE_TREE_FLAG_AMPERSAND |
            PARSE_TREE_FLAG_INTERRUPT_IMMUNE;
        tmp_parens->paren_subtree = intermediate;
        intermediate = tmp_parens;
    } else
        intermediate->flags |= PARSE_TREE_FLAG_AMPERSAND |
            PARSE_TREE_FLAG_INTERRUPT_IMMUNE;
    return do_ampersand_finish(o, intermediate);
}

static inline void do_right_paren(struct shell *self, int *parens)
{
    if (--*parens < 0)
        shell_set_error(self, SHELL_ERROR_TOO_MANY_RIGHT_PARENS);
}

static inline struct shell_parse_tree *finish(f_opts_t *o)
{
    if (o->parens == 0)
        return shell_parse_tree_from_lex_tree_part3(o->self, o->word_list,
            o->word_list_end, o->flags);
    shell_set_error(o->self, SHELL_ERROR_TOO_MANY_LEFT_PARENS);
    return NULL;
}
