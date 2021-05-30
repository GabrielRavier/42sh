/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_new_current_job
*/

#include "../proc.h"
#include "../../shell.h"

struct shell_proc *shell_proc_get_new_current_job(struct shell *self,
    struct shell_proc *proc)
{
    struct shell_proc *result = NULL;

    for (struct shell_proc *i = self->head_proc.next; i != NULL; i = i->next) {
        if (i != self->current_job_in_table && i != proc && i->pid != 0 &&
            i->pid == i->job_leader_pid) {
            if (i->flags & SH_PROC_FLAG_STOPPED)
                return i;
            if (result == NULL)
                result = i;
        }
    }
    return result;
}
