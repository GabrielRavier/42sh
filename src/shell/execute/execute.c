/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines execute
*/

#include "../execute.h"
#include "do_command.h"
#include "../fork.h"
#include "../flush_child_fds.h"

static bool shell_execute_do_list(struct shell *self,
    struct shell_parse_tree *parse_tree, MY_ATTR_UNUSED int *pipe_in,
    MY_ATTR_UNUSED int *pipe_out)
{
    if (parse_tree->node_left) {
        parse_tree->node_left->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(self, parse_tree->node_left, NULL, NULL))
            return false;
    }
    if (parse_tree->node_right) {
        parse_tree->node_right->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(self, parse_tree->node_right, NULL, NULL))
            return false;
    }
    return true;
}

static bool shell_execute_do_pipe(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    int pipe_node_pipe_fds[2];

    parse_tree->node_left->flags |= PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT |
        (parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_INPUT));
    if (!shell_execute(self, parse_tree->node_left, pipe_in,
        pipe_node_pipe_fds))
        return false;
    parse_tree->node_right->flags |= PARSE_TREE_NODE_FLAGS_PIPE_INPUT |
        (parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT));
    return shell_execute(self, parse_tree->node_right, pipe_node_pipe_fds,
        pipe_out);
}

static bool shell_execute_do_or_and(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    if (parse_tree->node_left) {
        parse_tree->node_left->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(self, parse_tree->node_left, pipe_in, pipe_out))
            return false;
        if ((self->last_command_exit_status == 0) != (parse_tree->type ==
            PARSE_TREE_NODE_TYPE_AND))
            return true;
    }
    if (parse_tree->node_right) {
        parse_tree->node_right->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(self, parse_tree->node_right, pipe_in, pipe_out))
            return false;
    }
    return true;
}

static bool (*EXECUTE_TYPE_FUNCTIONS[])(struct shell *,
    struct shell_parse_tree *, int *, int *) = {
    [PARSE_TREE_NODE_TYPE_LIST] = shell_execute_do_list,
    [PARSE_TREE_NODE_TYPE_COMMAND] = shell_execute_do_command,
    [PARSE_TREE_NODE_TYPE_PIPE] = shell_execute_do_pipe,
    [PARSE_TREE_NODE_TYPE_OR] = shell_execute_do_or_and,
    [PARSE_TREE_NODE_TYPE_AND] = shell_execute_do_or_and,
};

bool shell_execute(struct shell *self, struct shell_parse_tree *parse_tree,
    int *pipe_in, int *pipe_out)
{
    if (parse_tree == NULL)
        return true;
    if (parse_tree->type >= PARSE_TREE_NODE_TYPE_SMALLEST && parse_tree->type <=
        PARSE_TREE_NODE_TYPE_BIGGEST && !EXECUTE_TYPE_FUNCTIONS[
        parse_tree->type](self, parse_tree, pipe_in, pipe_out))
        return false;
    if (self->child_io_fds_setup)
        shell_flush_child_fds(self);
    return true;
}
