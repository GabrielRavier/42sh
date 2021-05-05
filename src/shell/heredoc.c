/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines heredoc
*/

#include "heredoc.h"
#include "set_error.h"
#include "print_error.h"
#include "../shell_char_vector.h"
#include "read_character.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

static void print_line_to_stdin(struct my_shell_char_vector *line_buffer)
{
    MY_CLEANUP_FREE char *line_as_c_str;

    line_buffer->data[line_buffer->size - 1] = '\n';
    my_shell_char_vector_append_single(line_buffer, '\0');
    line_as_c_str = shell_char_xstrdup_to_c(line_buffer->data);
    my_dputs(line_as_c_str, STDIN_FILENO);
}

static shell_char_t do_single_line(struct shell *self,
    struct my_shell_char_vector *line_buffer)
{
    shell_char_t c;

    while (true) {
        c = shell_read_character(self, true);
        if (c == SHELL_CHAR_ERROR || c == '\n')
            break;
        c &= SHELL_CHAR_NOT_QUOTE;
        if (c)
            my_shell_char_vector_append_single(line_buffer, c);
    }
    return c;
}

static void do_line_loop(struct shell *self, const shell_char_t *stop_line)
{
    struct my_shell_char_vector *line_buffer = my_shell_char_vector_new();
    shell_char_t c;

    while (true) {
        my_shell_char_vector_resize(line_buffer, 0);
        c = do_single_line(self, line_buffer);
        if (c == SHELL_CHAR_ERROR && line_buffer->size != 0)
            c = '\n';
        my_shell_char_vector_append_single(line_buffer, '\0');
        if (c == SHELL_CHAR_ERROR || shell_char_strcmp(line_buffer->data,
            stop_line) == 0)
            break;
        print_line_to_stdin(line_buffer);
    }
    my_shell_char_vector_free(line_buffer);
}

// TODO Add proper error handling here instead of forcing an exit
void shell_heredoc(struct shell *self, const shell_char_t *stop_line)
{
    char heredoc_name[] = "/tmp/sh.XXXXXX";

    my_close(STDIN_FILENO);
    if (my_mkstemp(heredoc_name) == -1) {
        shell_set_error(self, SHELL_ERROR_SYSTEM, heredoc_name,
            strerror(errno));
        ++self->child_depth;
        shell_print_error(self);
    }
    my_unlink(heredoc_name);
    do_line_loop(self, stop_line);
    my_lseek(STDIN_FILENO, 0, SEEK_SET);
}
