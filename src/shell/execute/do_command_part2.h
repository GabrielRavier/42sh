/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of do_command
*/

#pragma once

#include "do_command.h"
#include "../heredoc.h"
#include "../parse_tree.h"
#include "../signal.h"
#include "../close.h"
#include "../fork.h"

typedef struct {
    struct shell *self;
    struct shell_parse_tree *parse_tree;
    int *pipe_in;
    int *pipe_out;
    struct shell_builtin *builtin;
    bool has_forked;
    pid_t pid;
} sedcpf_opts_t;

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_execute_do_parent(
    struct shell *self, struct shell_parse_tree *parse_tree, int *pipe_in)
{
    if (!self->child_io_fds_setup && parse_tree->flags &
        PARSE_TREE_NODE_FLAGS_PIPE_INPUT) {
        shell_close(pipe_in[0]);
        shell_close(pipe_in[1]);
    }
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        return true;
    if (self->execute.no_sigchld) {
        sigprocmask(SIG_SETMASK, &self->execute.no_sigchld_old_set, NULL);
        self->execute.no_sigchld = false;
    }
    return shell_proc_wait_current(self);
}

MY_ATTR_WARN_UNUSED_RESULT static inline bool do_heredoc(struct shell *self,
    const shell_char_t *stop_line)
{
    int old_disable_sigint;
    bool result;

    if (self->should_set_interrupts && !shell_signal_enable_sigint(self,
        &old_disable_sigint))
        return false;
    result = shell_heredoc(self, stop_line);
    if (self->should_set_interrupts)
        self->disable_sigint = old_disable_sigint;
    return result;
}

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_execute_do_needed_fork(
    se_opts_t *o, bool *has_forked, pid_t *result)
{
    sigset_t chld_set;

    *has_forked = true;
    if (o->want_tty >= 0 && !o->self->execute.no_sigchld) {
        sigemptyset(&chld_set);
        sigaddset(&chld_set, SIGCHLD);
        sigprocmask(SIG_BLOCK, &chld_set, &o->self->execute.no_sigchld_old_set);
        o->self->execute.no_sigchld = true;
    }
    if (!shell_fork(o->self, o->parse_tree, o->want_tty, result))
        return false;
    if (result == 0 && o->self->execute.no_sigchld) {
        sigprocmask(SIG_SETMASK, &o->self->execute.no_sigchld_old_set, NULL);
        o->self->execute.no_sigchld = false;
    }
    return true;
}
