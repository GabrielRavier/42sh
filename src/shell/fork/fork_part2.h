/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of fork
*/

#pragma once

#include "../../shell.h"
#include "../set_and_print_error.h"
#include "my/cpp-like/algorithm.h"
#include "my/assert.h"
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

// We might need to set the tty process group ourselves, if there's a bunch of
// things that can run before an early command (such as before a builtin)
// We make sure we ignore the SIGTTOU that tcsetpgrp sends to all the processes
static inline void set_tty_pgrp(pid_t pgrp)
{
    struct sigaction old_action;

    if (tcgetpgrp(SHELL_TTY_FD) != pgrp) {
        sigaction(SIGTTOU, NULL, &old_action);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(SHELL_TTY_FD, pgrp);
        sigaction(SIGTTOU, NULL, &old_action);
    }
}

static inline void block_tstop_ttin(pid_t want_tty, sigset_t *old_set,
    bool *need_sigprocmask_cleanup)
{
    sigset_t tstp_ttin_set;

    if (want_tty > 0) {
        sigemptyset(&tstp_ttin_set);
        sigaddset(&tstp_ttin_set, SIGTSTP);
        sigaddset(&tstp_ttin_set, SIGTTIN);
        sigprocmask(SIG_BLOCK, &tstp_ttin_set, old_set);
        *need_sigprocmask_cleanup = true;
    }
}

// We block tty signals until everything's been set properly
// We also reset terminal_pgrp to 0 (if above 0) since we've given it away
// When we become the group leader, we want the tty: this is why we set want_tty
// to pgrp in that case
static inline void get_tty(struct shell *self, pid_t want_tty, pid_t pgrp)
{
    sigset_t old_set;
    bool need_sigprocmask_cleanup = false;

    block_tstop_ttin(want_tty, &old_set, &need_sigprocmask_cleanup);
    if (want_tty >= 0)
        if (setpgid(0, pgrp) == -1) {
            pgrp = getpid();
            if (setpgid(0, pgrp) == -1) {
                MY_ASSERT(self->child_depth != 0);
                shell_set_and_print_error(self, SHELL_ERROR_SYSTEM,
                    "setpgid child:\n", strerror(errno));
            }
            want_tty = pgrp;
        }
    if (want_tty > 0)
        set_tty_pgrp(pgrp);
    if (need_sigprocmask_cleanup)
        sigprocmask(SIG_SETMASK, &old_set, NULL);
    self->terminal_pgrp = MY_MIN(self->terminal_pgrp, 0);
}

// Children usually just die on SIGINT/SIGQUIT except in specific circumstances
// We also make sure to make the child stoppable
static inline void do_interrupts(struct shell *self, pid_t want_tty,
    bool ignore_int)
{
    self->should_set_interrupts = false;
    signal(SIGINT, ignore_int ? SIG_IGN : SIG_DFL);
    signal(SIGQUIT, ignore_int ? SIG_IGN : SIG_DFL);
    if (want_tty >= 0) {
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
    sigaction(SIGTERM, &self->parent_sigterm_action, NULL);
}
