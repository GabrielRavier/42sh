/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines print
*/

#include "../proc.h"
#include "../../shell.h"
#include "my/stdio.h"
#include <signal.h>

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

void shell_proc_print(struct shell *self, struct shell_proc *proc, int flags)
{
    int proc_status = proc->flags & SHELL_PROC_FLAG_ALL_STATUSES;

    if (flags & SHELL_PROC_PRINT_REASON_FILTERED) {
        switch (proc_status) {
        case SHELL_PROC_FLAG_RUNNING:
            my_dputs("Running ", self->error_output_fd);
            break;
        case SHELL_PROC_FLAG_STOPPED:
        case SHELL_PROC_FLAG_SIGNALED:
            if (proc->reason == SIGPIPE && proc->flags &
                SHELL_PROC_FLAG_PIPE_OUTPUT)
                break;
            if (MESSAGES[proc->reason % NSIG])
                my_dputs(MESSAGES[proc->reason % NSIG], self->error_output_fd);
            else
                my_dprintf(self->error_output_fd, "Signal %d", proc->reason);
        }
    }
    my_dputc('\n', self->error_output_fd);
}
