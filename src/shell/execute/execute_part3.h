/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines part 3 of execute
*/

#include "../execute.h"
#include "../set_error.h"
#include "../print_error.h"
#include "../../fd.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

// We copy our fds to the standard ones so that </dev/std{in,out,err} work
static inline void shell_execute_do_redirection_input_str(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    MY_CLEANUP_FREE char *tmp_filename;
    int fd;

    fd_copy(self->input_fd, STDIN_FILENO);
    fd_copy(self->output_fd, STDOUT_FILENO);
    fd_copy(self->error_output_fd, STDERR_FILENO);
    tmp_filename = shell_char_xstrdup_to_c(parse_tree->str_left);
    fd = my_open(tmp_filename, O_RDONLY);
    if (fd < 0) {
        shell_set_error(self, SHELL_ERROR_SYSTEM, tmp_filename,
            strerror(errno));
        shell_print_error(self);
    }
    fd_move(fd, STDIN_FILENO);
}

// INPUT_HEREDOC is handled by shell_heredoc
static inline void shell_execute_do_redirection_input(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in)
{
    if ((parse_tree->flags & PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC) == 0) {
        if (parse_tree->str_left != NULL)
            shell_execute_do_redirection_input_str(self, parse_tree);
        else if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_INPUT) {
            my_close(STDIN_FILENO);
            (void)dup(pipe_in[0]);
            my_close(pipe_in[0]);
            my_close(pipe_in[1]);
        } else {
            my_close(STDIN_FILENO);
            (void)dup(self->old_stdin_fd);
        }
    }
}

// We copy our fds to the standard ones so that >/dev/std{out,err} work
static inline void shell_execute_do_redirection_output_str(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    MY_CLEANUP_FREE char *tmp_filename = shell_char_xstrdup_to_c(
        parse_tree->str_right);
    int fd;

    fd_copy(self->output_fd, STDOUT_FILENO);
    fd_copy(self->error_output_fd, STDERR_FILENO);
    fd = (parse_tree->flags & PARSE_TREE_NODE_FLAGS_APPEND) ? open(
        tmp_filename, O_WRONLY | O_APPEND) : 0;
    if ((parse_tree->flags & PARSE_TREE_NODE_FLAGS_APPEND) == 0 || fd < 0) {
        fd = my_creat(tmp_filename, 0666);
        if (fd < 0) {
            shell_set_error(self, SHELL_ERROR_SYSTEM, tmp_filename,
                strerror(errno));
            shell_print_error(self);
        }
    }
    fd_move(fd, STDOUT_FILENO);
}

static inline void shell_execute_do_redirection_output(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_out)
{
    if (parse_tree->str_right != NULL)
        shell_execute_do_redirection_output_str(self, parse_tree);
    else {
        my_close(STDOUT_FILENO);
        dup((parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT) ?
            pipe_out[1] : self->output_fd);
    }
}

static inline void shell_execute_do_redirection(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    if (self->child_io_fds_setup)
        return;
    shell_execute_do_redirection_input(self, parse_tree, pipe_in);
    shell_execute_do_redirection_output(self, parse_tree, pipe_out);
    my_close(STDERR_FILENO);
    dup(self->error_output_fd);
    self->child_io_fds_setup = true;
}
