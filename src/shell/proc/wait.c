/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines wait
*/

#include "../proc.h"
#include "wait_part2.h"
#include "my/assert.h"

static int wait_for_proc(struct shell *self, struct shell_proc *proc)
{
    int job_flags;
    struct shell_proc *i = proc;

    while (true) {
        do_next_wait(self);
        job_flags = 0;
        do {
            job_flags |= i->flags;
            i = i->next_in_job_list;
        } while (i != proc);
        if ((job_flags & SHELL_PROC_FLAG_RUNNING) == 0)
            return job_flags;
    }
}

static void finish(struct shell *self, struct shell_proc *proc, int job_flags)
{
    struct shell_proc *i = proc;
    int reason = 0;

    if ((job_flags & (SHELL_PROC_FLAG_SIGNALED | SHELL_PROC_FLAG_STOPPED)) ||
        i->current_dir == NULL || shell_char_strcmp(self->current_dir->name,
        i->current_dir->name) != 0) {
        if (job_flags & SHELL_PROC_FLAG_STOPPED)
            shell_putchar(self, '\n');
        shell_proc_print(self, proc, SHELL_PROC_PRINT_REASON_FILTERED |
            SHELL_PROC_PRINT_SHELL_DIR_IF_DIFF);
    }
    i = proc;
    do {
        if (i->reason)
            reason = i->flags & (SHELL_PROC_FLAG_SIGNALED |
                SHELL_PROC_FLAG_INTERRUPTED) ? i->reason | 0x80 : i->reason;
        i = i->next_in_job_list;
    } while (i != proc);
    self->last_command_exit_status = reason;
    shell_proc_flush(self, proc);
}

// The assert is to check that we're not waiting on a non-foreground job
void shell_proc_wait(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;

    while (proc->pid != proc->job_leader_pid)
        proc = proc->next_in_job_list;
    i = proc;
    do {
        MY_ASSERT((i->flags & (SHELL_PROC_FLAG_FOREGROUND |
            SHELL_PROC_FLAG_RUNNING)) != SHELL_PROC_FLAG_RUNNING);
        i = i->next_in_job_list;
    } while (i != proc);
    finish(self, proc, wait_for_proc(self, proc));
}
