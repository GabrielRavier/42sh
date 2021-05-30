/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines any_stopped
*/

#include "../proc.h"
#include "../../shell.h"
#include "../set_error.h"

#include "../printf.h"

bool shell_proc_any_stopped(struct shell *self, bool need_newline)
{
    self->check_stop = 2;
    for (struct shell_proc *i = self->head_proc.next; i != NULL; i = i->next)
        if (i->flags & SH_PROC_FLAG_STOPPED) {
            shell_set_error(self, SHELL_ERROR_THERE_ARE_SUSPENDED_JOBS,
                need_newline ? "\n" : "");
            return false;
        }
    return true;
}
