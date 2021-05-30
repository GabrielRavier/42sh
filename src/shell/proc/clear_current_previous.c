/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines clear_current_previous
*/

#include "../proc.h"
#include "../../shell.h"

void shell_proc_clear_current_previous(struct shell *self,
    struct shell_proc *proc)
{
    if (proc == self->current_job_in_table) {
        self->current_job_in_table = (self->previous_job_in_table != NULL) ?
            self->previous_job_in_table : shell_proc_get_new_current_job(self,
            proc);
        self->previous_job_in_table = shell_proc_get_new_current_job(self,
            proc);
    } else if (proc == self->previous_job_in_table)
        self->previous_job_in_table = shell_proc_get_new_current_job(self,
            proc);
}
