/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines free
*/

#include "../lexical_word_list.h"
#include "my/stdlib.h"

void lexical_word_list_free(struct lexical_word_list *self)
{
    struct lexical_word_list *to_free;

    while (self->next != self) {
        to_free = self->next;
        self->next = self->next->next;
        my_free(to_free->word);
        my_free(to_free);
    }
    self->prev = self;
}
