/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines init
*/

#include "../lexical_word_list.h"
#include <stddef.h>

void lexical_word_list_init(struct lexical_word_list *self)
{
    self->word = NULL;
    self->prev = self;
    self->next = self;
}
