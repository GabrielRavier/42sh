/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines lex_tree_to_parse_tree
*/

#include "../parse_tree.h"
#include "from_lex_tree.h"
#include "from_lex_tree_part2.h"

struct shell_parse_tree *shell_parse_tree_from_lex_tree(struct shell *self,
    struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
        case ';':
        case '&':
        case '\n':
            continue;
        default:
            return shell_parse_tree_from_lex_tree_part2(self, i, word_list_end,
                flags);
        }
    return NULL;
}
