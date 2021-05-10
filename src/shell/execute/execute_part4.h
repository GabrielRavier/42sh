/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 4 of execute
*/

#pragma once

#include "../../shell.h"
#include "../parse_tree.h"
#include "../execute.h"

static inline void shell_execute_do_or_and(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    if (parse_tree->node_left) {
        parse_tree->node_left->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        shell_execute(self, parse_tree->node_left, pipe_in, pipe_out);
        if ((self->last_command_exit_status == 0) != (parse_tree->type ==
            PARSE_TREE_NODE_TYPE_AND))
            return;
    }
    if (parse_tree->node_right) {
        parse_tree->node_right->flags |= parse_tree->flags &
            PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE;
        shell_execute(self, parse_tree->node_right, pipe_in, pipe_out);
    }
}
