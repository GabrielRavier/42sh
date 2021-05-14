/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines do_command
*/

#include "../execute.h"
#include "do_command_part2.h"
#include "do_redirection.h"
#include "do_exec.h"
#include "../fixup.h"
#include "../heredoc.h"
#include "../builtin.h"
#include "../pipe.h"
#include "../fork.h"
#include "../print_error.h"
#include "my/string.h"
#include <unistd.h>

// result is whether or not the caller should return (i.e. there's nothing to
// do)
static bool shell_execute_do_command_pre_fork(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_out, bool *result)
{
    if ((parse_tree->argv[0][0] & (SHELL_CHAR_QUOTED |
        SHELL_CHAR_NOT_QUOTED)) == SHELL_CHAR_QUOTED)
        my_memmove(parse_tree->argv[0], parse_tree->argv[0] + 1,
            (shell_char_strlen(parse_tree->argv[0] + 1) + 1) * sizeof(
            *parse_tree->argv[0]));
    if (!shell_fixup_parse_tree(self, parse_tree))
        return false;
    if (parse_tree->argv[0] == NULL) {
        *result = true;
        return true;
    }
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        shell_pipe(self, pipe_out);
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC)
        shell_heredoc(self, parse_tree->str_left);
    self->last_command_exit_status = 0;
    *result = false;
    return true;
}

static void shell_execute_do_builtin_or_exec(struct shell *self,
    struct shell_parse_tree *parse_tree, struct shell_builtin *builtin,
    bool has_forked)
{
    if (builtin) {
        shell_builtin_run(self, builtin, parse_tree);
        if (self->error != NULL)
            shell_print_error(self);
        if (has_forked)
            exit(self->last_command_exit_status);
        return;
    }
    shell_execute_do_exec(self, parse_tree);
}

static void shell_execute_do_command_post_fork(sedcpf_opts_t *o)
{
    if (o->pid != 0) {
        shell_execute_do_parent(o->self, o->parse_tree, o->pipe_in);
        return;
    }
    shell_execute_do_redirection(o->self, o->parse_tree, o->pipe_in,
        o->pipe_out);
    if (o->parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT) {
        close(o->pipe_out[0]);
        close(o->pipe_out[1]);
    }
    shell_execute_do_builtin_or_exec(o->self, o->parse_tree, o->builtin,
        o->has_forked);
}

static pid_t shell_execute_do_fork_if_needed(struct shell *self,
    struct shell_parse_tree *parse_tree, struct shell_builtin *builtin,
    bool *has_forked)
{
    if (!builtin || parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT) {
        *has_forked = true;
        return shell_fork(self, parse_tree);
    }
    return 0;
}

bool shell_execute_do_command(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    struct shell_builtin *builtin;
    bool has_forked = false;
    pid_t pid;
    bool should_return;

    if (!shell_execute_do_command_pre_fork(self, parse_tree, pipe_out,
        &should_return))
        return false;
    if (should_return)
        return true;
    builtin = shell_builtin_find(parse_tree);
    pid = shell_execute_do_fork_if_needed(self, parse_tree, builtin,
        &has_forked);
    shell_execute_do_command_post_fork(&((sedcpf_opts_t){self, parse_tree,
        pipe_in, pipe_out, builtin, has_forked, pid}));
    return true;
}
