/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines free
*/

#include "../dir.h"
#include "my/stdlib.h"

void dir_free(struct dir *self)
{
    if (self->ref_count != 0) {
        self->next = NULL;
        self->prev = NULL;
    } else {
        my_free(self->name);
        my_free(self);
    }
}
