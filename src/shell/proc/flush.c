/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines flush
*/

#include "../proc.h"
#include "../../shell.h"
#include "my/cpp-like/algorithm.h"
#include "my/assert.h"

static void do_index(struct shell *self, int index)
{
    int new_max_index = 0;

    if (index == self->proc_max_index) {
        for (struct shell_proc *i = self->head_proc.next; i != NULL; i =
            i->next)
            new_max_index = MY_MAX(new_max_index, i->index);
        self->proc_max_index = new_max_index;
    }
}

// The initial MY_ASSERT is to make sure we don't try to flush a process twice
void shell_proc_flush(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;
    int index;

    MY_ASSERT(proc->pid != 0);
    while (proc->pid != proc->job_leader_pid)
        proc = proc->next_in_job_list;
    shell_proc_clear_current_previous(self, proc);
    if (proc == self->current_job)
        self->current_job = NULL;
    index = proc->index;
    i = proc;
    do {
        i->index = 0;
        i->pid = 0;
        i = i->next_in_job_list;
    } while (i != proc);
    do_index(self, index);
}
