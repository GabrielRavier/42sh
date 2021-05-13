/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines process
*/

#include "process.h"
#include "flush_output_buffer.h"
#include "lex.h"
#include "parse_tree/from_lex_tree.h"
#include "execute.h"
#include "print_error.h"
#include "printf.h"
#include "my/stdio.h"
#include <unistd.h>

static bool do_line(struct shell *self)
{
    struct shell_parse_tree *parse_tree;
    bool result = true;

    self->error = NULL;
    lexical_word_list_free(&self->current_lexical_word);
    shell_lex(self, &self->current_lexical_word);
    parse_tree = shell_parse_tree_from_lex_tree(self,
        self->current_lexical_word.next,
        &self->current_lexical_word, 0);
    if (self->error) {
        shell_parse_tree_free(parse_tree);
        return false;
    }
    result = shell_execute(self, parse_tree, NULL, NULL);
    shell_parse_tree_free(parse_tree);
    return result;
}

void shell_process(struct shell *self)
{
    while (true) {
        if (self->error != NULL)
            shell_print_error(self);
        if (self->input_is_tty) {
            shell_printf(self, "> ");
            shell_flush_output_buffer(self);
        }
        if (!do_line(self))
            continue;
    }
}
