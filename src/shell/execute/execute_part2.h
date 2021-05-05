/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of execute
*/

#include "../execute.h"
#include "../pipe.h"
#include "../heredoc.h"
#include "../builtin.h"
#include "../print_error.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include "my/string.h"
#include <stdlib.h>

_Noreturn static inline void shell_execute_do_exec(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    char **argv = shell_char_xdup_strv_to_c(parse_tree->argv);

    my_execvp(argv[0], argv);
    my_dprintf(self->error_output_fd, "%s: Command not found.\n", argv[0]);
    exit(1);
}

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

static inline bool shell_execute_do_command_pre_fork(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_out)
{
    if ((parse_tree->argv[0][0] & (SHELL_CHAR_QUOTE | SHELL_CHAR_NOT_QUOTE)) ==
        SHELL_CHAR_QUOTE)
        my_memmove(parse_tree->argv[0], parse_tree->argv[0] + 1,
            (shell_char_strlen(parse_tree->argv[0] + 1) + 1) * sizeof(
            *parse_tree->argv[0]));
    if (parse_tree->argv[0] == NULL)
        return false;
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        shell_pipe(self, pipe_out);
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC)
        shell_heredoc(self, parse_tree->str_left);
    self->last_command_exit_status = 0;
    return true;
}

static inline void shell_execute_do_builtin_or_exec(struct shell *self,
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
