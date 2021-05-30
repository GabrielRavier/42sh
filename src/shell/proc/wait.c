/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines wait
*/

#include "../proc.h"
#include "wait_part2.h"
#include "../putchar.h"
#include "../signal.h"
#include "../printf.h"
#include "my/assert.h"
#include <unistd.h>

static void do_set_init(sigset_t *old_set, sigset_t *pause_set)
{
    sigset_t int_chld_set;

    sigemptyset(&int_chld_set);
    sigaddset(&int_chld_set, SIGINT);
    sigaddset(&int_chld_set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &int_chld_set, old_set);
    *pause_set = *old_set;
    sigdelset(pause_set, SIGCHLD);
    sigaddset(pause_set, SIGINT);
}

MY_ATTR_WARN_UNUSED_RESULT static int get_all_job_list_flags(
    struct shell_proc *proc)
{
    int result = 0;
    struct shell_proc *i = proc;

    do {
        result |= i->flags;
        i = i->next_in_job_list;
    } while (i != proc);
    return result;
}

MY_ATTR_WARN_UNUSED_RESULT static bool wait_for_proc(struct shell *self,
    struct shell_proc *proc, int *result)
{
    struct shell_proc *i = proc;
    sigset_t old_set;
    sigset_t pause_set;

    do_set_init(&old_set, &pause_set);
    while (true) {
        if (!shell_signal_handle_pending(self)) {
            sigprocmask(SIG_SETMASK, &old_set, NULL);
            return false;
        }
        *result = get_all_job_list_flags(i);
        if ((*result & SHELL_PROC_FLAG_RUNNING) == 0) {
            sigprocmask(SIG_SETMASK, &old_set, NULL);
            return true;
        }
        SHELL_DEBUG_PRINTF(self,
            "%jd sigsuspending waiting for SIGCHLD on %jd\n",
            (intmax_t)getpid(), (intmax_t)i->pid);
        sigsuspend(&pause_set);
    }
}

static bool finish(struct shell *self, struct shell_proc *proc, int job_flags)
{
    if (self->terminal_pgrp)
        tcsetpgrp(SHELL_TTY_FD, self->terminal_pgrp);
    if ((job_flags & (SHELL_PROC_FLAG_SIGNALED | SHELL_PROC_FLAG_STOPPED)) ||
        proc->current_dir == NULL || shell_char_strcmp(self->current_dir->name,
        proc->current_dir->name) != 0) {
        if (job_flags & SHELL_PROC_FLAG_STOPPED)
            shell_putchar(self, '\n');
        shell_proc_print(self, proc, SHELL_PROC_PRINT_REASON_FILTERED |
            SHELL_PROC_PRINT_SHELL_DIR_IF_DIFF);
    }
    if (!finish_do_interactive_interrupted(self, proc, job_flags))
        return false;
    finish_do_status(self, proc);
    return true;
}

// The assert is to check that we're not waiting on a non-foreground job
bool shell_proc_wait(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;
    int job_flags;

    while (proc->pid != proc->job_leader_pid)
        proc = proc->next_in_job_list;
    i = proc;
    do {
        MY_ASSERT((i->flags & (SHELL_PROC_FLAG_FOREGROUND |
            SHELL_PROC_FLAG_RUNNING)) != SHELL_PROC_FLAG_RUNNING);
        i = i->next_in_job_list;
    } while (i != proc);
    return !wait_for_proc(self, proc, &job_flags) ? false : finish(self, proc,
        job_flags);
}
