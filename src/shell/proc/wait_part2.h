/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines part 2 of wait
*/

#pragma once

#include "../proc.h"
#include "../../shell.h"
#include "../putchar.h"
#include <sys/wait.h>
#include <sys/types.h>

static inline void do_next_wait_found_set_status_reason(struct shell_proc *i,
    int status)
{
    if (WIFSTOPPED(status)) {
        i->flags |= SHELL_PROC_FLAG_STOPPED;
        i->reason = WSTOPSIG(status);
    } else {
        if (WIFSIGNALED(status)) {
            if (WTERMSIG(status) == SIGINT)
                i->flags |= SHELL_PROC_FLAG_INTERRUPTED;
            else
                i->flags |= SHELL_PROC_FLAG_SIGNALED;
            if (WCOREDUMP(status))
                i->flags |= SHELL_PROC_FLAG_DUMPED_CORE;
            i->reason = WTERMSIG(status);
        } else {
            i->reason = WEXITSTATUS(status);
            i->flags |= (i->reason != 0) ? SHELL_PROC_FLAG_ABNORMAL_EXIT :
                SHELL_PROC_FLAG_NORMAL_EXIT;
        }
    }
}

static inline int make_job_flags(struct shell_proc *i)
{
    int result = 0;
    struct shell_proc *j = i;

    do {
        result |= j->flags;
        j = j->next_in_job_list;
    } while (j != i);
    return result;
}

static inline void do_next_wait_found_not_running_or_reported(
    struct shell *self, struct shell_proc *proc, int job_flags)
{
    struct shell_proc *i = proc;

    do {
        if (i->flags & SHELL_PROC_FLAG_STOPPED)
            i->flags |= SHELL_PROC_FLAG_REPORTED;
        i = i->next_in_job_list;
    } while (i != proc);
    while (i->pid != i->job_leader_pid)
        i = i->next_in_job_list;
    if (job_flags & SHELL_PROC_FLAG_STOPPED) {
        if (self->current_job != NULL && self->current_job != i)
            self->previous_job_in_table = self->current_job;
        self->current_job = i;
    } else
        shell_proc_clear_current_previous(self, i);
    if ((job_flags & SHELL_PROC_FLAG_FOREGROUND) && (!(job_flags & (
        SHELL_PROC_FLAG_SIGNALED | SHELL_PROC_FLAG_STOPPED) || i->current_dir ==
        NULL || shell_char_strcmp(self->current_dir->name, i->current_dir->name)
        != 0)) && (job_flags & SHELL_PROC_FLAG_INTERRUPTED))
        shell_putchar(self, '\n');
}

static inline void do_next_wait_found(struct shell *self,
    struct shell_proc *proc, int status)
{
    int job_flags;

    proc->flags &= ~(SHELL_PROC_FLAG_RUNNING | SHELL_PROC_FLAG_STOPPED |
        SHELL_PROC_FLAG_REPORTED);
    do_next_wait_found_set_status_reason(proc, status);
    job_flags = make_job_flags(proc);
    proc->flags &= ~SHELL_PROC_FLAG_FOREGROUND;
    if ((job_flags & (SHELL_PROC_FLAG_RUNNING | SHELL_PROC_FLAG_REPORTED)) == 0)
        do_next_wait_found_not_running_or_reported(self, proc, job_flags);
}

static inline void do_next_wait(struct shell *self)
{
    int status;
    pid_t pid = wait(&status);
    struct shell_proc *i = self->head_proc.next;

    if (pid == 0 || pid == -1)
        return;
    for (; i != NULL; i = i->next)
        if (pid == i->pid)
            do_next_wait_found(self, i, status);
}
