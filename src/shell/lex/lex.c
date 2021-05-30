/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines lex
*/

#include "../lex.h"
#include "get_word.h"
#include "../read_character.h"
#include "../unread_character.h"
#include "my/stdlib.h"
#include <stddef.h>

static bool do_lex_loop(struct shell *self, struct lexical_word_list *result,
    struct lexical_word_list *work_list)
{
    struct lexical_word_list *new_entry;

    do {
        new_entry = my_xmalloc(sizeof(*new_entry));
        new_entry->word = NULL;
        new_entry->prev = work_list;
        work_list->next = new_entry;
        new_entry->next = result;
        result->prev = new_entry;
        work_list = new_entry;
        if (!shell_lex_get_word(self, &work_list->word))
            return false;
    } while (work_list->word[0] != '\n');
    return true;
}

// Note: We make sure to set up new_entry entirely so that if shell_lex_get_word
// fails, the work list can still be freed properly
bool shell_lex(struct shell *self, struct lexical_word_list *result)
{
    shell_char_t c;
    struct lexical_word_list *work_list;

    do
        if (!shell_read_character(self, false, &c))
            return false;
    while (c == ' ' || c == '\t');
    shell_unread_character(self, c);
    lexical_word_list_init(result);
    work_list = result;
    return do_lex_loop(self, result, work_list);
}
