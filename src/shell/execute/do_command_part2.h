/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of do_command
*/

#pragma once

#include "do_command.h"
#include "../parse_tree.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <stdlib.h>

typedef struct {
    struct shell *self;
    struct shell_parse_tree *parse_tree;
    int *pipe_in;
    int *pipe_out;
    struct shell_builtin *builtin;
    bool has_forked;
    pid_t pid;
} sedcpf_opts_t;

static void shell_execute_do_parent(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in)
{
    if (!self->child_io_fds_setup && parse_tree->flags &
        PARSE_TREE_NODE_FLAGS_PIPE_INPUT) {
        my_close(pipe_in[0]);
        my_close(pipe_in[1]);
    }
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        return;
    shell_proc_wait_current(self);
    return;
}

_Noreturn static void shell_execute_do_exec(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    char **argv = shell_char_xdup_strv_to_c(parse_tree->argv);

    my_execvp(argv[0], argv);
    my_dprintf(self->error_output_fd, "%s: Command not found.\n", argv[0]);
    for (size_t i = 0; argv[i] != NULL; ++i)
        my_free(argv[i]);
    my_free(argv);
    exit(1);
}
