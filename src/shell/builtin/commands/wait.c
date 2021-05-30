/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin wait
*/

#include "../commands.h"
#include "../../signal.h"

static void do_loop(struct shell *self, sigset_t *pause_set)
{
    int old_disable_sigint;
    bool handle_pending_result;

    for (struct shell_proc *i = self->head_proc.next; i != NULL; i = i->next)
        if (i->pid != 0 && i->flags & SH_PROC_FLAG_RUNNING) {
            sigsuspend(pause_set);
            old_disable_sigint = self->disable_sigint;
            self->disable_sigint = 0;
            handle_pending_result = shell_signal_handle_pending(self);
            self->disable_sigint = old_disable_sigint;
            if (!handle_pending_result)
                break;
        }
}

// This makes the shell wait for everything to have finished
void shell_builtin_wait(struct shell *self, shell_char_t **argv)
{
    sigset_t pause_set;
    sigset_t chld_block_set;
    sigset_t old_set;

    (void)argv;
    self->print_jobs_on_int = true;
    sigprocmask(SIG_BLOCK, NULL, &pause_set);
    sigdelset(&pause_set, SIGCHLD);
    if (self->should_set_interrupts)
        sigdelset(&pause_set, SIGINT);
    sigprocmask(SIG_BLOCK, NULL, &chld_block_set);
    sigaddset(&chld_block_set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &chld_block_set, &old_set);
    if (shell_signal_handle_pending(self))
        do_loop(self, &pause_set);
    self->print_jobs_on_int = false;
    sigprocmask(SIG_SETMASK, &old_set, NULL);
}
