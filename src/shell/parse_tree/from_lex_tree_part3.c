/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines from_lex_tree_part3
*/

#include "from_lex_tree_part3.h"
#include "from_lex_tree_part3_internal.h"
#include "from_lex_tree.h"
#include "from_lex_tree_part4.h"
#include "../parse_tree.h"
#include "my/cpp-like/utility.h"
#include "my/stdlib.h"

static struct shell_parse_tree *do_newline_list(dnl_opts_t *o)
{
    struct shell_parse_tree *result = my_xcalloc(1, sizeof(*result));

    result->type = PARSE_TREE_TYPE_LIST;
    result->node_left = shell_parse_tree_from_lex_tree_part4(o->self,
        o->word_list, o->i, o->flags);
    result->node_right = shell_parse_tree_from_lex_tree(o->self, o->i->next,
        o->word_list_end, o->flags);
    if (result->node_right == NULL)
        MY_SWAP(result->node_right, result->node_left);
    return result;
}

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part3(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    int parens = 0;

    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
            PARSER_SWITCH_PARENS_CASES(parens);
        case ';':
        case '\n':
            if (parens != 0)
                continue;
            return do_newline_list(&((dnl_opts_t){self, word_list,
                word_list_end, flags, i}));
        }
    return shell_parse_tree_from_lex_tree_part4(self, word_list, word_list_end,
        flags);
}
