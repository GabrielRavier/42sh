/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines from_lex_tree_part7
*/

#include "from_lex_tree_part7.h"
#include "from_lex_tree_part7_part2.h"
#include "from_lex_tree_part2.h"
#include "my/stdlib.h"

static void do_right_paren(struct parse_part7_state *st)
{
    --st->parens;
    if (st->parens == 0)
        st->right_paren_word = st->i;
}

static void do_default(struct parse_part7_state *st)
{
    if (st->parens != 0)
        return;
    if (st->self->error.text == NULL)
        st->parse_tree->argv[st->argument_count++] =
            shell_char_xstrdup(st->i->word);
}

static void do_loop(struct parse_part7_state *st)
{
    for (st->i = st->word_list; st->i != st->word_list_end; st->i = st->i->next)
        switch (st->i->word[0]) {
        case '(':
            do_left_paren(st);
            continue;
        case ')':
            do_right_paren(st);
            continue;
        case '>':
            do_output(st);
            continue;
        case '<':
            do_input(st);
            continue;
        default:
            do_default(st);
            continue;
        }
}

static struct shell_parse_tree *finish(struct parse_part7_state *st)
{
    if (st->left_paren_word != NULL) {
        if (st->argument_count != 0)
            shell_set_error(st->self, SHELL_ERROR_BADLY_PLACED_PARENS);
        my_free(st->parse_tree->argv);
        st->parse_tree->argv = NULL;
        st->parse_tree->type = PARSE_TREE_TYPE_PARENS;
        st->parse_tree->paren_subtree = shell_parse_tree_from_lex_tree_part2(
            st->self, st->left_paren_word, st->right_paren_word,
            PARSER_FLAGS_PARENS);
    } else {
        if (st->argument_count == 0)
            shell_set_error(st->self, SHELL_ERROR_NULL_COMMAND);
        st->parse_tree->type = PARSE_TREE_TYPE_COMMAND;
    }
    return st->parse_tree;
}

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part7(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags)
{
    struct parse_part7_state st = {self, word_list, word_list_end, flags,
        my_xcalloc(1, sizeof(*st.parse_tree)), NULL, 0, 0, NULL, NULL};

    st.parse_tree->argv = my_xcalloc(get_argument_count(&st) +
        1, sizeof(st.parse_tree->argv));
    st.parens = 0;
    if (word_list_end->word[0] == ')')
        st.parse_tree->flags = PARSE_TREE_FLAG_NO_FORK;
    do_loop(&st);
    return finish(&st);
}

