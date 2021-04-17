/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines do_line
*/

#include "../do_line.h"
#include "../lex.h"
#include "../parse_tree/from_lex_tree.h"
#include "../print_error.h"
#include "../execute.h"
#include "my/my_string.h"

void shell_do_line(struct shell *self)
{
    struct shell_parse_tree *parse_tree;

    self->error = NULL;
    lexical_word_list_free(&self->current_lexical_word);
    shell_lex(self, &self->current_lexical_word);
    parse_tree = shell_parse_tree_from_lex_tree(self,
        self->current_lexical_word.next,
        &self->current_lexical_word, 0);
    if (!self->error)
        shell_execute(self, parse_tree, NULL, NULL);
    else
        shell_print_error(self, false);
    shell_parse_tree_free(parse_tree);
}
