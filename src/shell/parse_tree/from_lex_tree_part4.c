/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines from_lex_tree_part4
*/

#include "from_lex_tree_part4.h"
#include "from_lex_tree.h"
#include "from_lex_tree_part5.h"
#include "../parse_tree.h"
#include "my/stdlib.h"

static struct shell_parse_tree *make_result(struct shell_parse_tree *left,
     struct shell_parse_tree *right)
{
    struct shell_parse_tree *result = my_calloc(1, sizeof(*result));

    result->type = PARSE_TREE_TYPE_OR;
    result->node_left = left;
    result->node_right = right;
    return result;
}

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part4(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    int parens = 0;

    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
            PARSER_SWITCH_PARENS_CASES(parens);
        case '|':
            if (i->word[1] != '|' || parens != 0)
                continue;
            return make_result(shell_parse_tree_from_lex_tree_part5(self,
                word_list, i, flags), shell_parse_tree_from_lex_tree_part4(self,
                i->next, word_list_end, flags));
        }
    return shell_parse_tree_from_lex_tree_part5(self, word_list, word_list_end,
        flags);
}
