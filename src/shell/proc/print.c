/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines print
*/

#include "../proc.h"
#include "print_part2.h"

void shell_proc_print(struct shell *self, struct shell_proc *proc, int flags)
{
    bool old_handling_error = self->handling_error;
    int job_flags = 0;
    struct shell_proc *first_proc = proc;
    int status = -1;
    int reason = -1;

    self->handling_error = true;
    while (proc->pid != proc->job_leader_pid)
        proc = proc->next_in_job_list;
    do
        do_loop_iter(&((dli_opts_t){self, proc, first_proc, flags, &reason,
            &status, &job_flags}));
    while (do_continue(self, &proc, first_proc, flags));
    self->handling_error = old_handling_error;
}
