/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines end_job
*/

#include "../proc.h"
#include "../../shell.h"
#include "../printf.h"
#include "../putchar.h"

void shell_proc_end_job(struct shell *self)
{
    struct shell_proc *proc;
    struct shell_proc *i;

    if (self->current_job && (self->current_job->flags & (
        SHELL_PROC_FLAG_FOREGROUND | SHELL_PROC_FLAG_STOPPED)) == 0) {
        proc = self->current_job;
        self->current_job = NULL;
        while (proc->pid != proc->job_leader_pid)
            proc = proc->next_in_job_list;
        shell_printf(self, "[%d]", proc->index);
        i = proc;
        do {
            shell_printf(self, " %jd", (intmax_t)i->pid);
            i = i->next_in_job_list;
        } while (i != proc);
        shell_putchar(self, '\n');
    }
    self->current_job = NULL;
}
