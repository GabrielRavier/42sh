/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines do_redirection
*/

#include "do_redirection.h"
#include "../set_error.h"
#include "../print_error.h"
#include "../parse_tree.h"
#include "../close.h"
#include "../creat.h"
#include "../open.h"
#include "../../fd.h"
#include "my/stdlib.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// We copy our fds to the standard ones so that </dev/std{in,out,err} work
static void shell_execute_do_redirection_input_str(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    MY_CLEANUP_FREE char *tmp_filename;
    int fd;

    fd_copy(self->input_fd, STDIN_FILENO);
    fd_copy(self->output_fd, STDOUT_FILENO);
    fd_copy(self->error_output_fd, STDERR_FILENO);
    tmp_filename = shell_char_xstrdup_to_c(parse_tree->str_left);
    fd = shell_open(tmp_filename, O_RDONLY);
    if (fd < 0) {
        shell_set_error(self, SHELL_ERROR_SYSTEM, tmp_filename,
            strerror(errno));
        shell_print_error(self);
    }
    fd_move(fd, STDIN_FILENO);
}

// INPUT_HEREDOC is handled by shell_heredoc
static void shell_execute_do_redirection_input(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in)
{
    if ((parse_tree->flags & PARSE_TREE_FLAG_INPUT_HEREDOC) == 0) {
        if (parse_tree->str_left != NULL)
            shell_execute_do_redirection_input_str(self, parse_tree);
        else if (parse_tree->flags & PARSE_TREE_FLAG_PIPE_INPUT) {
            shell_close(STDIN_FILENO);
            (void)dup(pipe_in[0]);
            shell_close(pipe_in[0]);
            shell_close(pipe_in[1]);
        } else if ((parse_tree->flags & PARSE_TREE_FLAG_INTERRUPT_IMMUNE) &&
            self->terminal_pgrp == -1) {
            shell_close(STDIN_FILENO);
            shell_open("/dev/null", O_RDONLY);
        } else {
            shell_close(STDIN_FILENO);
            (void)dup(self->old_stdin_fd);
            fcntl(STDIN_FILENO, F_SETFD, 0);
        }
    }
}

// We copy our fds to the standard ones so that >/dev/std{out,err} work
static void shell_execute_do_redirection_output_str(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    MY_CLEANUP_FREE char *tmp_filename = shell_char_xstrdup_to_c(
        parse_tree->str_right);
    int fd;

    fd_copy(self->output_fd, STDOUT_FILENO);
    fd_copy(self->error_output_fd, STDERR_FILENO);
    fd = (parse_tree->flags & PARSE_TREE_FLAG_APPEND) ? shell_open(
        tmp_filename, O_WRONLY | O_APPEND) : 0;
    if ((parse_tree->flags & PARSE_TREE_FLAG_APPEND) == 0 || fd < 0) {
        fd = shell_creat(tmp_filename, 0666);
        if (fd < 0) {
            shell_set_error(self, SHELL_ERROR_SYSTEM, tmp_filename,
                strerror(errno));
            shell_print_error(self);
        }
    }
    fd_move(fd, STDOUT_FILENO);
}

static void shell_execute_do_redirection_output(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_out)
{
    if (parse_tree->str_right != NULL)
        shell_execute_do_redirection_output_str(self, parse_tree);
    else if (parse_tree->flags & PARSE_TREE_FLAG_PIPE_OUTPUT) {
        shell_close(STDOUT_FILENO);
        dup(pipe_out[1]);
    } else {
        shell_close(STDOUT_FILENO);
        dup(self->output_fd);
        fcntl(STDOUT_FILENO, F_SETFD, 0);
    }
}

void shell_execute_do_redirection(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
{
    if (self->child_io_fds_setup)
        return;
    shell_execute_do_redirection_input(self, parse_tree, pipe_in);
    shell_execute_do_redirection_output(self, parse_tree, pipe_out);
    shell_close(STDERR_FILENO);
    dup(self->error_output_fd);
    fcntl(STDERR_FILENO, F_SETFD, 0);
    self->child_io_fds_setup = true;
}
