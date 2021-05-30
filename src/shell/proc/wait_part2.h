/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of wait
*/

#pragma once

#include "../../shell.h"
#include "../signal.h"
#include <stdbool.h>

MY_ATTR_WARN_UNUSED_RESULT static inline bool finish_do_interactive_interrupted(
    struct shell *self, struct shell_proc *proc, int job_flags)
{
    if ((job_flags & (SHELL_PROC_FLAG_INTERRUPTED | SHELL_PROC_FLAG_STOPPED)) &&
        self->should_set_interrupts) {
        if ((job_flags & SHELL_PROC_FLAG_STOPPED) == 0)
            shell_proc_flush(self, proc);
        if (!shell_signal_process_int(self, false))
            return false;
    }
    return true;
}

static inline void finish_do_status(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i = proc;
    int reason = 0;

    do {
        if (i->reason)
            reason = i->flags & (SHELL_PROC_FLAG_SIGNALED |
                SHELL_PROC_FLAG_INTERRUPTED) ? i->reason | 0x80 : i->reason;
        i = i->next_in_job_list;
    } while (i != proc);
    self->last_command_exit_status = reason;
    shell_proc_flush(self, proc);
}
