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

static bool shell_execute_do_list(se_opts_t *o)
{
    if (o->parse_tree->node_left) {
        o->parse_tree->node_left->flags |= o->parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
            NULL, NULL, o->want_tty})))
            return false;
    }
    if (o->parse_tree->node_right) {
        o->parse_tree->node_right->flags |= o->parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
            NULL, NULL, o->want_tty})))
            return false;
    }
    return true;
}

static bool shell_execute_do_pipe(se_opts_t *o)
{
    int pipe_node_pipe_fds[2];

    o->parse_tree->node_left->flags |= PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT |
        (o->parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_INPUT));
    if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
        o->pipe_in, pipe_node_pipe_fds, o->want_tty})))
        return false;
    o->parse_tree->node_right->flags |= PARSE_TREE_NODE_FLAGS_PIPE_INPUT |
        (o->parse_tree->flags & (PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT));
    return shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
        pipe_node_pipe_fds, o->pipe_out, o->want_tty}));
}

static bool shell_execute_do_or_and(se_opts_t *o)
{
    if (o->parse_tree->node_left) {
        o->parse_tree->node_left->flags |= o->parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
            o->pipe_in, o->pipe_out, o->want_tty})))
            return false;
        if ((o->self->last_command_exit_status == 0) != (o->parse_tree->type ==
            PARSE_TREE_NODE_TYPE_AND))
            return true;
    }
    if (o->parse_tree->node_right) {
        o->parse_tree->node_right->flags |= o->parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
            o->pipe_in, o->pipe_out, o->want_tty})))
            return false;
    }
    return true;
}

static shell_execute_like_func_t *const EXECUTE_TYPE_FUNCTIONS[] = {
    [PARSE_TREE_NODE_TYPE_LIST] = shell_execute_do_list,
    [PARSE_TREE_NODE_TYPE_COMMAND] = shell_execute_do_command,
    [PARSE_TREE_NODE_TYPE_PIPE] = shell_execute_do_pipe,
    [PARSE_TREE_NODE_TYPE_OR] = shell_execute_do_or_and,
    [PARSE_TREE_NODE_TYPE_AND] = shell_execute_do_or_and,
};

bool shell_execute(se_opts_t *o)
{
    if (o->parse_tree == NULL)
        return true;
    if (o->parse_tree->type >= PARSE_TREE_NODE_TYPE_SMALLEST &&
        o->parse_tree->type <= PARSE_TREE_NODE_TYPE_BIGGEST &&
        !EXECUTE_TYPE_FUNCTIONS[o->parse_tree->type](o))
        return false;
    if (o->self->child_io_fds_setup)
        shell_flush_child_fds(o->self);
    return true;
}
