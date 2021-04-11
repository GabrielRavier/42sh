/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines lex
*/

#include "../lex.h"
#include "get_word.h"
#include "../read_character.h"
#include "../unread_character.h"
#include "my/stdlib.h"
#include <stddef.h>

void shell_lex(struct shell *self, struct lexical_word_list *result)
{
    int c;
    struct lexical_word_list *work_list;
    struct lexical_word_list *new_entry;

    do
        c = shell_read_character(self, false);
    while (c == ' ' || c == '\t');
    shell_unread_character(self, c);
    lexical_word_list_init(result);
    work_list = result;
    do {
        new_entry = my_xmalloc(sizeof(*new_entry));
        new_entry->word = NULL;
        new_entry->prev = work_list;
        work_list->next = new_entry;
        new_entry->next = result;
        result->prev = new_entry;
        work_list = new_entry;
        work_list->word = shell_lex_get_word(self);
    } while (work_list->word[0] != '\n');
}
