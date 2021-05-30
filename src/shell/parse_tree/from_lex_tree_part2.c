/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines from_lex_tree_part2
*/

#include "from_lex_tree_part2.h"
#include "from_lex_tree_part2_part2.h"

static const shell_char_t AND[] = {'&', '\0'};

static void do_pipe_above(struct lexical_word_list **i,
    struct lexical_word_list *word_list_end)
{
    if ((*i)->word[0] == '|' && (*i)->word[1] == '|')
        return;
    if ((*i)->next != word_list_end && shell_char_strcmp((*i)->next->word,
        AND) == 0)
        *i = (*i)->next;
}

static bool do_loop_iter(dli_opts_t *o)
{
    switch ((*o->i)->word[0]) {
    case '(':
        ++*o->parens;
        return false;
    case ')':
        do_right_paren(o->self, o->parens);
        return false;
    case '|':
    case '>':
        do_pipe_above(o->i, o->word_list_end);
        return false;
    case '&':
        if (*o->parens != 0 || (*o->i)->word[1] == '&')
            return false;
        *o->result = do_ampersand(o);
        return true;
    }
    return false;
}

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part2(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    int parens = 0;
    struct shell_parse_tree *result;

    for (struct lexical_word_list *i = word_list; i != word_list_end; i =
        i->next)
        if (do_loop_iter(&((dli_opts_t){self, word_list, word_list_end, flags,
            &parens, &i, &result})))
            return result;
    return finish(&((f_opts_t){self, word_list, word_list_end, flags, parens}));
}
