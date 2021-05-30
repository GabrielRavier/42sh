/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines do_command
*/

#include "../execute.h"
#include "do_command_part2.h"
#include "do_exec.h"
#include "do_redirection.h"
#include "../fixup.h"
#include "../pipe.h"
#include "../builtin.h"
#include "../print_error.h"
#include "../exit_from_status.h"
#include "my/string.h"

// *result is whether or not the caller should return (i.e. there's nothing to
// do)
static bool shell_execute_do_command_pre_fork(se_opts_t *o, bool *result)
{
    if ((o->parse_tree->argv[0][0] & (SHELL_CHAR_QUOTED |
        SHELL_CHAR_NOT_QUOTED)) == SHELL_CHAR_QUOTED)
        my_memmove(o->parse_tree->argv[0], o->parse_tree->argv[0] + 1,
            (shell_char_strlen(o->parse_tree->argv[0] + 1) + 1) * sizeof(
            *o->parse_tree->argv[0]));
    if (!shell_fixup_parse_tree(o->self, o->parse_tree))
        return false;
    if (o->parse_tree->argv[0] == NULL) {
        *result = true;
        return true;
    }
    if (o->parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        shell_pipe(o->self, o->pipe_out);
    if (o->parse_tree->flags & PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC)
        if (!do_heredoc(o->self, o->parse_tree->str_left))
            return false;
    o->self->last_command_exit_status = 0;
    *result = false;
    return true;
}

static void shell_execute_do_builtin_or_exec(struct shell *self,
    struct shell_parse_tree *parse_tree, struct shell_builtin *builtin,
    bool has_forked)
{
    bool old_handling_error = self->handling_error;

    if (builtin) {
        shell_builtin_run(self, builtin, parse_tree);
        if (self->error.text != NULL)
            shell_print_error(self);
        self->handling_error = old_handling_error;
        if (has_forked)
            exit(self->last_command_exit_status);
        return;
    }
    shell_execute_do_exec(self, parse_tree);
}

MY_ATTR_WARN_UNUSED_RESULT static bool shell_execute_do_command_post_fork(
    se_opts_t *o, struct shell_builtin *builtin, bool has_forked, pid_t pid)
{
    if (pid != 0)
        return shell_execute_do_parent(o->self, o->parse_tree, o->pipe_in);
    shell_execute_do_redirection(o->self, o->parse_tree, o->pipe_in,
        o->pipe_out);
    if (o->parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT) {
        shell_close(o->pipe_out[0]);
        shell_close(o->pipe_out[1]);
    }
    shell_execute_do_builtin_or_exec(o->self, o->parse_tree, builtin,
        has_forked);
    return true;
}

static pid_t shell_execute_do_fork_if_needed(se_opts_t *o,
    struct shell_builtin *builtin, bool *has_forked, pid_t *result)
{
    if (!builtin || o->parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        return shell_execute_do_needed_fork(o, has_forked, result);
    *result = 0;
    return true;
}

bool shell_execute_do_command(se_opts_t *o)
{
    struct shell_builtin *builtin;
    bool has_forked = false;
    pid_t pid;
    bool should_return;

    if (!shell_execute_do_command_pre_fork(o, &should_return))
        return false;
    if (should_return)
        return true;
    builtin = shell_builtin_find(o->parse_tree);
    return !shell_execute_do_fork_if_needed(o, builtin, &has_forked, &pid) ?
        false : shell_execute_do_command_post_fork(o, builtin, has_forked, pid);
}
