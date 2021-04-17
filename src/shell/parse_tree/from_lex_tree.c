/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines lex_tree_to_parse_tree
*/

#include "from_lex_tree.h"
#include "from_lex_tree_part2.h"
#include "../set_error.h"
#include "my/cpp-like/algorithm.h"
#include "my/cpp-like/utility.h"
#include "my/stdlib.h"

static struct shell_parse_tree *parse_part3(struct shell *self,
    struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    struct shell_parse_tree *result;

    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
        case '|':
            result = my_xcalloc(1, sizeof(*result));
            result->type = PARSE_TREE_NODE_TYPE_PIPE;
            result->node_left = parse_part4(self, word_list, i,
                flags | PARSER_FLAGS_OUTPUT);
            result->node_right = parse_part3(self, i->next, word_list_end,
                flags | PARSER_FLAGS_INPUT);
            return result;
        }
    return parse_part4(self, word_list, word_list_end, flags);
}

static struct shell_parse_tree *parse_part2(struct shell *self,
    struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    struct shell_parse_tree *result;

    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
        case ';':
        case '\n':
            result = my_xcalloc(1, sizeof(*result));
            result->type = PARSE_TREE_NODE_TYPE_LIST;
            result->node_left = parse_part3(self, word_list, i, flags);
            result->node_right = shell_parse_tree_from_lex_tree(self, i->next,
                word_list_end, flags);
            if (result->node_right == NULL)
                MY_SWAP(result->node_right, result->node_left);
            return result;
        }
    return parse_part3(self, word_list, word_list_end, flags);
}

struct shell_parse_tree *shell_parse_tree_from_lex_tree(struct shell *self,
    struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    for (struct lexical_word_list *i = word_list; i != word_list_end;
        i = i->next)
        switch (i->word[0]) {
        case ';':
        case '\n':
            continue;
        default:
            return parse_part2(self, i, word_list_end, flags);
        }
    return NULL;
}
