/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of print
*/

#pragma once

#include "../../shell.h"
#include "../printf.h"
#include "../putchar.h"
#include "my/assert.h"
#include <signal.h>
#include <stdbool.h>

typedef struct {
    struct shell *self;
    struct shell_proc *proc;
    int flags;
    int reason;
    int status;
} ds_opts_t;

typedef struct {
    struct shell *self;
    struct shell_proc *proc;
    struct shell_proc *first_proc;
    int flags;
    int *reason;
    int *status;
    int *job_flags;
} dli_opts_t;

static const char *const MESSAGES[NSIG] = {
    [SIGHUP] = "Hangup",
    [SIGINT] = "Interrupt",
    [SIGQUIT] = "Quit",
    [SIGILL] = "Illegal instruction",
    [SIGTRAP] = "Trace/BPT trap",
    [SIGABRT] = "Abort",
    [SIGFPE] = "Floating exception",
    [SIGKILL] = "Killed",
    [SIGUSR1] = "User signal 1",
    [SIGUSR2] = "User signal 2",
    [SIGSEGV] = "Segmentation fault",
    [SIGBUS] = "Bus error",
    [SIGSYS] = "Bad system call",
    [SIGPIPE] = "Broken pipe",
    [SIGALRM] = "Alarm clock",
    [SIGTERM] = "Terminated",
    [SIGCHLD] = "Child stopped or exited",
    [SIGPWR] = "Power failure",
    [SIGURG] = "Urgent condition on I/O channel",
    [SIGSTOP] = "Suspended (signal)",
    [SIGTSTP] = "Suspended",
    [SIGCONT] = "Continued",
    [SIGTTIN] = "Suspended (tty input)",
    [SIGTTOU] = "Suspended (tty output)",
    [SIGWINCH] = "Window size changed",
    [SIGXCPU] = "Cputime limit exceeded",
    [SIGXFSZ] = "Filesize limit exceeded",
    [SIGVTALRM] = "Virtual time alarm",
    [SIGPROF] = "Profiling time alert",
    [SIGPOLL] = "Pollable event occured",
    [SIGSTKFLT] = "Stack limit exceeded",
};

static inline bool do_continue(struct shell *self, struct shell_proc **proc,
    struct shell_proc *first_proc, int flags)
{
    if ((flags & SHELL_PROC_PRINT_REASON_FILTERED) && (*proc)->flags &
        SHELL_PROC_FLAG_DUMPED_CORE)
        shell_printf(self, "(core dumped)");
    if (first_proc == (*proc)->next_in_job_list && self->line_buffer !=
        self->line_buffer_current_ptr)
        shell_putchar(self, '\n');
    *proc = (*proc)->next_in_job_list;
    return *proc != first_proc;
}

static inline void do_switch_signal(ds_opts_t *o)
{
    if ((o->flags & SHELL_PROC_PRINT_REASON_FILTERED) && o->reason !=
        SIGINT && (o->reason != SIGPIPE || (o->proc->flags &
        SHELL_PROC_FLAG_PIPE_OUTPUT) == 0)) {
        if (MESSAGES[o->proc->reason % NSIG] == NULL)
            shell_printf(o->self, "Signal %d", o->proc->reason % NSIG);
        else
            shell_printf(o->self, "%s", MESSAGES[o->proc->reason % NSIG]);
    } else
        o->reason = -1;
}

// We do nothing on NORMAL_EXIT or ABNORMAL_EXIT, but the assert makes sure we
// didn't forget to handle some future status or something like that
static inline void do_switch(ds_opts_t *o)
{
    switch (o->status) {
    case SHELL_PROC_FLAG_RUNNING:
        shell_printf(o->self, "Running ");
        break;
    case SHELL_PROC_FLAG_INTERRUPTED:
    case SHELL_PROC_FLAG_STOPPED:
    case SHELL_PROC_FLAG_SIGNALED:
        do_switch_signal(o);
        break;
    default:
        MY_ASSERT(o->status == SHELL_PROC_FLAG_NORMAL_EXIT || o->status ==
            SHELL_PROC_FLAG_ABNORMAL_EXIT);
    }
}

static inline void do_loop_iter_reason(dli_opts_t *o, int proc_status)
{
    if (proc_status == *o->status) {
        if (o->proc->reason == *o->reason)
            return;
        else
            *o->reason = o->proc->reason;
    } else {
        *o->status = proc_status;
        *o->reason = o->proc->reason;
    }
    do_switch(&((ds_opts_t){o->self, o->proc, o->flags, *o->reason,
        *o->status}));
}

static inline void do_loop_iter(dli_opts_t *o)
{
    bool not_first = o->proc != o->first_proc;
    int proc_status = o->proc->flags & SHELL_PROC_FLAG_ALL_STATUSES;

    *o->job_flags |= o->proc->flags;
    if (not_first && o->self->line_buffer != o->self->line_buffer_current_ptr)
        shell_putchar(o->self, ' ');
    else if (o->flags & SHELL_PROC_PRINT_REASON_FILTERED)
        do_loop_iter_reason(o, proc_status);
}
