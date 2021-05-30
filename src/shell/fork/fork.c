/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines fork
*/

#include "../fork.h"
#include "fork_part2.h"
#include "../signal.h"
#include "../set_error.h"
#include "../printf.h"

static bool finish(struct shell *self, pid_t want_tty, bool result)
{
    if (want_tty < 0)
        if (!shell_signal_decr_disable(self, &self->disable_sigchld))
            return false;
    return result;
}

static void do_child(struct shell *self, struct shell_parse_tree *parse_tree,
    pid_t want_tty, bool ignore_int)
{
    pid_t process_group = self->current_job ?
        self->current_job->job_leader_pid : getpid();

    SHELL_DEBUG_PRINTF(self, "New forked child with pid %jd\n",
        (intmax_t)getpid());
    self->disable_sigchld = 0;
    shell_proc_flush_all(self);
    self->current_job = NULL;
    ++self->child_depth;
    if (self->should_set_interrupts)
        do_interrupts(self, want_tty, ignore_int);
    else if (self->terminal_pgrp == -1 && (parse_tree->flags &
        PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE)) {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
    get_tty(self, want_tty, process_group);
}

// If setpgid fails, that means the leader must have died. We thus flush the
// current job and make ourselves the process leader (the parent will eventually
// find out)
// Note: if the second setpgid fails, we're already in the right group, so we
// don't care
static void do_parent(struct shell *self, struct shell_parse_tree *parse_tree,
    pid_t want_tty, const pid_t *result)
{
    if (want_tty >= 0) {
        if (setpgid(*result, self->current_job ?
            self->current_job->job_leader_pid : *result) == -1 && errno ==
            EPERM) {
            self->current_job = NULL;
            setpgid(*result, *result);
        }
    }
    shell_proc_add(self, *result, parse_tree);
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_fork_loop(struct shell *self,
    pid_t want_tty, pid_t *result)
{
    while (true) {
        *result = fork();
        if (*result != -1)
            break;
        if (!self->should_set_interrupts)
            sleep(1);
        else {
            shell_set_error(self, SHELL_ERROR_NO_MORE_PROCESSES);
            return finish(self, want_tty, false);
        }
    }
    return true;
}

// If there's more than 16 nested shells, we explode: This is to avoid forking
// loops. We also make sure we don't get SIGCHLD until we've put the process in
// our list
bool shell_fork(struct shell *self, struct shell_parse_tree *parse_tree,
    pid_t want_tty, pid_t *result)
{
    bool ignore_int = self->should_set_interrupts && (self->terminal_pgrp ==
        -1 && (parse_tree->flags & PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE));

    if (self->child_depth >= 16) {
        shell_set_error(self, SHELL_ERROR_FORK_NESTING, 16);
        return false;
    }
    if (want_tty < 0)
        ++self->disable_sigchld;
    if (!do_fork_loop(self, want_tty, result))
        return false;
    if (*result == 0)
        do_child(self, parse_tree, want_tty, ignore_int);
    else
        do_parent(self, parse_tree, want_tty, result);
    return finish(self, want_tty, true);
}
