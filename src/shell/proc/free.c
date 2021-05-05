/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines free
*/

#include "../proc.h"
#include "my/stdlib.h"

void shell_proc_free(struct shell_proc *self)
{
    if (self->current_dir && --self->current_dir->ref_count == 0 &&
        self->current_dir->next == NULL)
        dir_free(self->current_dir);
    my_free(self);
}
