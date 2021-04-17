/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines add
*/

#include "../proc.h"
#include "../parse_tree.h"
#include "../../shell.h"
#include "my/assert.h"
#include "my/stdlib.h"

void shell_proc_add(struct shell *self, pid_t pid,
    struct shell_parse_tree *parse_tree)
{
    struct shell_proc *proc = &self->current_proc;

    proc->pid = pid;
    proc->flags = SHELL_PROC_FLAG_RUNNING | SHELL_PROC_FLAG_FOREGROUND;
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        proc->flags |= SHELL_PROC_FLAG_PIPE_OUTPUT;
}
