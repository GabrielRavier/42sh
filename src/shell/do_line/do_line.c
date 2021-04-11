/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines do_line
*/

#include "../do_line.h"
#include "../lex.h"
#include "my/my_string.h"

void shell_do_line(struct shell *self)
{
    //struct shell_parse_tree *parse_tree;

    lexical_word_list_free(&self->current_lexical_word);
    shell_lex(self, &self->current_lexical_word);
    __auto_type p1 = self->current_lexical_word.next;
    __auto_type p2 = &self->current_lexical_word;
    while (p1 != p2) {
        __auto_type word_it = p1->word;
        while (*word_it)
            putchar(*word_it++);
        putchar('\n');
        p1 = p1->next;
    }
    /*parse_tree = shell_parse_words(self->current_lexical_word.next,
      &self->current_lexical_word);*/
}
