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

// Note: If someone does command & command, we make a new job after the first
// command
static bool shell_execute_do_list(se_opts_t *o)
{
    if (o->parse_tree->node_left) {
        o->parse_tree->node_left->flags |= o->parse_tree->flags &
            PARSE_TREE_FLAG_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
            NULL, NULL, o->want_tty})))
            return false;
        if (o->parse_tree->node_left->flags & PARSE_TREE_FLAG_AMPERSAND &&
            o->parse_tree->node_right && (o->parse_tree->node_right->flags &
            PARSE_TREE_FLAG_AMPERSAND) == 0)
            shell_proc_end_job(o->self);
    }
    if (o->parse_tree->node_right) {
        o->parse_tree->node_right->flags |= o->parse_tree->flags &
            (PARSE_TREE_FLAG_INTERRUPT_IMMUNE | PARSE_TREE_FLAG_NO_FORK);
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
            NULL, NULL, o->want_tty})))
            return false;
    }
    return true;
}

static bool shell_execute_do_pipe(se_opts_t *o)
{
    int pipe_node_pipe_fds[2];

    o->parse_tree->node_left->flags |= PARSE_TREE_FLAG_PIPE_OUTPUT |
        (o->parse_tree->flags & (PARSE_TREE_FLAG_PIPE_INPUT |
        PARSE_TREE_FLAG_AMPERSAND | PARSE_TREE_FLAG_INTERRUPT_IMMUNE));
    if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
        o->pipe_in, pipe_node_pipe_fds, o->want_tty})))
        return false;
    o->parse_tree->node_right->flags |= PARSE_TREE_FLAG_PIPE_INPUT |
        (o->parse_tree->flags & (PARSE_TREE_FLAG_PIPE_OUTPUT |
        PARSE_TREE_FLAG_AMPERSAND | PARSE_TREE_FLAG_NO_FORK |
        PARSE_TREE_FLAG_INTERRUPT_IMMUNE));
    return shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
        pipe_node_pipe_fds, o->pipe_out, o->want_tty}));
}

static bool shell_execute_do_or_and(se_opts_t *o)
{
    if (o->parse_tree->node_left) {
        o->parse_tree->node_left->flags |= o->parse_tree->flags &
            PARSE_TREE_FLAG_INTERRUPT_IMMUNE;
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_left,
            o->pipe_in, o->pipe_out, o->want_tty})))
            return false;
        if ((o->self->last_command_exit_status == 0) != (o->parse_tree->type ==
            PARSE_TREE_TYPE_AND))
            return true;
    }
    if (o->parse_tree->node_right) {
        o->parse_tree->node_right->flags |= o->parse_tree->flags &
            (PARSE_TREE_FLAG_INTERRUPT_IMMUNE | PARSE_TREE_FLAG_NO_FORK);
        if (!shell_execute(&((se_opts_t){o->self, o->parse_tree->node_right,
            o->pipe_in, o->pipe_out, o->want_tty})))
            return false;
    }
    return true;
}

static shell_execute_like_func_t *const EXECUTE_TYPE_FUNCTIONS[] = {
    [PARSE_TREE_TYPE_LIST] = shell_execute_do_list,
    [PARSE_TREE_TYPE_COMMAND] = shell_execute_do_command,
    [PARSE_TREE_TYPE_PARENS] = shell_execute_do_command,
    [PARSE_TREE_TYPE_PIPE] = shell_execute_do_pipe,
    [PARSE_TREE_TYPE_OR] = shell_execute_do_or_and,
    [PARSE_TREE_TYPE_AND] = shell_execute_do_or_and,
};

// When we have an & command, don't do tty stuff
bool shell_execute(se_opts_t *o)
{
    if (o->parse_tree == NULL)
        return true;
    if (o->parse_tree->flags & PARSE_TREE_FLAG_AMPERSAND)
        o->want_tty = 0;
    if (o->parse_tree->type >= PARSE_TREE_TYPE_SMALLEST &&
        o->parse_tree->type <= PARSE_TREE_TYPE_BIGGEST &&
        !EXECUTE_TYPE_FUNCTIONS[o->parse_tree->type](o))
        return false;
    if (o->self->child_io_fds_setup)
        shell_flush_child_fds(o->self);
    return true;
}
