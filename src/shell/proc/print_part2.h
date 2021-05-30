/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of print
*/

#pragma once

#include "../proc.h"
#include "../../shell.h"
#include "print_part3.h"

typedef struct {
    struct shell *self;
    struct shell_proc *proc;
    struct shell_proc *first_proc;
    int flags;
    int *reason;
    int *status;
    int *job_flags;
} dli_opts_t;

static inline void do_loop_iter_reason(dli_opts_t *o, int proc_status)
{
    const char *format = (o->flags & SHELL_PROC_PRINT_NAME) ? "%-30s" : "%s";

    if (proc_status == *o->status) {
        if (o->proc->reason == *o->reason) {
            shell_printf(o->self, format, "");
            return;
        }
        else
            *o->reason = o->proc->reason;
    } else {
        *o->status = proc_status;
        *o->reason = o->proc->reason;
    }
    do_switch(&((ds_opts_t){o->self, o->proc, o->flags, *o->reason,
        *o->status, format}));
}

static inline void do_number(dli_opts_t *o, bool not_first)
{
    if (o->flags & SHELL_PROC_PRINT_NUMBER) {
        if (!not_first)
            shell_printf(o->self, "[%d]%s %c ", o->proc->index, o->proc->index <
                10 ? " " : "", o->proc == o->self->current_job_in_table ? '+' :
                (o->proc == o->self->previous_job_in_table ? '-' : ' '));
        else
            shell_printf(o->self, "       ");
    }
}

static inline void do_loop_iter(dli_opts_t *o)
{
    bool not_first = o->proc != o->first_proc;
    int proc_status = o->proc->flags & SH_PROC_FLAG_ALL_STATUSES;

    *o->job_flags |= o->proc->flags;
    if (not_first && o->self->line_buffer != o->self->line_buffer_current_ptr &&
        !(o->flags & SHELL_PROC_PRINT_FANCY) && ((proc_status == *o->status &&
        o->proc->reason == *o->reason) || !(o->flags &
        SHELL_PROC_PRINT_REASON)))
        shell_putchar(o->self, ' ');
    else {
        if (not_first && o->self->line_buffer !=
            o->self->line_buffer_current_ptr)
            shell_putchar(o->self, '\n');
        do_number(o, not_first);
        if (o->flags & SHELL_PROC_PRINT_FANCY)
            shell_printf(o->self, "%5jd ", (intmax_t)o->proc->pid);
        if (o->flags & (SHELL_PROC_PRINT_REASON_FILTERED |
            SHELL_PROC_PRINT_REASON))
            do_loop_iter_reason(o, proc_status);
    }
}
