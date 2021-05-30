/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 3 of print
*/

#pragma once

#include "../proc.h"
#include "../../shell.h"
#include "../putchar.h"
#include "../printf.h"
#include "my/assert.h"
#include "my/stdio.h"
#include "my/stdlib.h"

static inline void do_wd_now(struct shell *self, struct shell_proc **proc,
    struct shell_proc *first_proc, int flags)
{
    if (first_proc == (*proc)->next_in_job_list) {
        if (self->line_buffer != self->line_buffer_current_ptr)
            shell_putchar(self, '\n');
        if (flags & SHELL_PROC_PRINT_SHELL_DIR_IF_DIFF && shell_char_strcmp(
            first_proc->current_dir->name, self->current_dir->name) != 0)
            shell_printf(self, "(wd now: %s)\n", shell_char_static_xstrdup_to_c(
                self->current_dir->name));
    }
}

// TOOD: Make it so that the "(wd: dir)" part is translate to make dir be
// translated when a home directory is part of it, like tcsh (same for the
// "wd now" part)
static inline bool do_continue(struct shell *self, struct shell_proc **proc,
    struct shell_proc *first_proc, int flags)
{
    if (flags & SHELL_PROC_PRINT_NAME) {
        shell_printf(self, "%s", "TODO: actually print commands");
        if ((*proc)->flags & SH_PROC_FLAG_PIPE_OUTPUT)
            shell_printf(self, " |");
    }
    if ((flags & (SHELL_PROC_PRINT_REASON | SHELL_PROC_PRINT_REASON_FILTERED) &&
        (*proc)->flags & SH_PROC_FLAG_DUMPED_CORE))
        shell_printf(self, " (core dumped)");
    if (first_proc == (*proc)->next_in_job_list && (flags &
        SHELL_PROC_PRINT_JOB_DIR_IF_DIFF && shell_char_strcmp(
        first_proc->current_dir->name, self->current_dir->name) != 0))
        shell_printf(self, " (wd: %s)", shell_char_static_xstrdup_to_c(
            first_proc->current_dir->name));
    do_wd_now(self, proc, first_proc, flags);
    *proc = (*proc)->next_in_job_list;
    return *proc != first_proc;
}

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

typedef struct {
    struct shell *self;
    struct shell_proc *proc;
    int flags;
    int reason;
    int status;
    const char *format;
} ds_opts_t;

static inline void do_switch_signal(ds_opts_t *o)
{
    char *intermediate;

    if ((o->flags & SHELL_PROC_PRINT_REASON) || ((o->flags &
        SHELL_PROC_PRINT_REASON_FILTERED) && o->reason != SIGINT &&
        (o->reason != SIGPIPE || (o->proc->flags & SH_PROC_FLAG_PIPE_OUTPUT) ==
        0))) {
        if (MESSAGES[o->proc->reason % NSIG] == NULL)
            my_xasprintf(&intermediate, "Signal %d", o->proc->reason % NSIG);
        else
            my_xasprintf(&intermediate, "%s", MESSAGES[o->proc->reason % NSIG]);
        shell_printf(o->self, o->format, intermediate);
        my_free(intermediate);
    } else
        o->reason = -1;
}

// We do nothing on NORMAL_EXIT or ABNORMAL_EXIT, but the assert makes sure we
// didn't forget to handle some future status or something like that
static inline void do_switch(ds_opts_t *o)
{
    switch (o->status) {
    case SH_PROC_FLAG_RUNNING:
        shell_printf(o->self, o->format, "Running ");
        break;
    case SH_PROC_FLAG_INTERRUPTED:
    case SH_PROC_FLAG_STOPPED:
    case SH_PROC_FLAG_SIGNALED:
        do_switch_signal(o);
        break;
    case SH_PROC_FLAG_NORMAL_EXIT:
    case SH_PROC_FLAG_ABNORMAL_EXIT:
        if (o->flags & SHELL_PROC_PRINT_REASON) {
            if (o->proc->reason)
                shell_printf(o->self, "Exit %-25d", o->proc->reason);
            else
                shell_printf(o->self, o->format, "Done");
        }
        break;
    }
}
