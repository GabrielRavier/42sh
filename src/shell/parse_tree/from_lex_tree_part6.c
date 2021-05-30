/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines from_lex_tree_part6
*/

#include "from_lex_tree_part6.h"
#include "from_lex_tree_part7.h"
#include "from_lex_tree.h"
#include "../parse_tree.h"
#include "my/stdlib.h"

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part6(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    struct shell_parse_tree *result;
    int parens = 0;

    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
            PARSER_SWITCH_PARENS_CASES(parens);
        case '|':
            if (parens != 0)
                continue;
            result = my_xcalloc(1, sizeof(*result));
            result->type = PARSE_TREE_TYPE_PIPE;
            result->node_left = shell_parse_tree_from_lex_tree_part7(self,
                word_list, i, flags | PARSER_FLAGS_OUTPUT);
            result->node_right = shell_parse_tree_from_lex_tree_part6(self,
                i->next, word_list_end, flags | PARSER_FLAGS_INPUT);
            return result;
        }
    return shell_parse_tree_from_lex_tree_part7(self, word_list, word_list_end,
        flags);
}
