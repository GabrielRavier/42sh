/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush
*/

#include "../proc.h"
#include "../../shell.h"
#include "my/assert.h"

void shell_proc_flush(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;

    MY_ASSERT(proc->pid != 0);
    while (proc->pid != proc->job_leader_pid)
        proc = proc->next_in_job_list;
    shell_proc_clear_current_previous(self, proc);
    if (proc == self->current_job)
        self->current_job = NULL;
    i = proc;
    do {
        i->pid = 0;
        i = i->next_in_job_list;
    } while (i != proc);
}
