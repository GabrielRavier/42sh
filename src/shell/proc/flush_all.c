/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush_all
*/

#include "../proc.h"
#include "../../shell.h"

void shell_proc_flush_all(struct shell *self)
{
    for (struct shell_proc *i = self->head_proc.next; i != NULL; i = i->next)
        if (i->pid != 0)
            shell_proc_flush(self, i);
}
