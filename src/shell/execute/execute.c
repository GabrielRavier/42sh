/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines execute
*/

#include "../execute.h"
#include "execute_part2.h"
#include "execute_part3.h"
#include "execute_part4.h"
#include "../fork.h"
#include "../flush_child_fds.h"

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

static void shell_execute_do_command(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    struct shell_builtin *builtin;
    bool has_forked = false;
    pid_t pid;

    if (!shell_execute_do_command_pre_fork(self, parse_tree, pipe_out))
        return;
    builtin = shell_builtin_find(parse_tree);
    pid = shell_execute_do_fork_if_needed(self, parse_tree, builtin,
        &has_forked);
    if (pid != 0) {
        shell_execute_do_parent(self, parse_tree, pipe_in);
        return;
    }
    shell_execute_do_redirection(self, parse_tree, pipe_in, pipe_out);
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT) {
        close(pipe_out[0]);
        close(pipe_out[1]);
    }
    shell_execute_do_builtin_or_exec(self, parse_tree, builtin, has_forked);
}

static void shell_execute_do_list(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    if (parse_tree->node_left) {
        parse_tree->node_left->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        shell_execute(self, parse_tree->node_left, NULL, NULL);
    }
    if (parse_tree->node_right) {
        parse_tree->node_right->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        shell_execute(self, parse_tree->node_right, NULL, NULL);
    }
}

static void shell_execute_do_pipe(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    int pipe_node_pipe_fds[2];

    parse_tree->node_left->flags |= PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT |
        (parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_INPUT));
    shell_execute(self, parse_tree->node_left, pipe_in, pipe_node_pipe_fds);
    parse_tree->node_right->flags |= PARSE_TREE_NODE_FLAGS_PIPE_INPUT |
        (parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT));
    shell_execute(self, parse_tree->node_right, pipe_node_pipe_fds, pipe_out);
}

void shell_execute(struct shell *self, struct shell_parse_tree *parse_tree,
    int *pipe_in, int *pipe_out)
{
    if (parse_tree == NULL)
        return;
    switch (parse_tree->type) {
    case PARSE_TREE_NODE_TYPE_LIST:
        shell_execute_do_list(self, parse_tree);
        break;
    case PARSE_TREE_NODE_TYPE_COMMAND:
        shell_execute_do_command(self, parse_tree, pipe_in, pipe_out);
        break;
    case PARSE_TREE_NODE_TYPE_PIPE:
        shell_execute_do_pipe(self, parse_tree, pipe_in, pipe_out);
        break;
    case PARSE_TREE_NODE_TYPE_AND:
    case PARSE_TREE_NODE_TYPE_OR:
        shell_execute_do_or_and(self, parse_tree, pipe_in, pipe_out);
        break;
    }
    if (self->child_io_fds_setup)
        shell_flush_child_fds(self);
}
