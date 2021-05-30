/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines heredoc
*/

#include "heredoc.h"
#include "set_error.h"
#include "print_error.h"
#include "read_character.h"
#include "close.h"
#include "../shell_char_vector.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include <stdlib.h>
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

MY_ATTR_WARN_UNUSED_RESULT static bool do_single_line(struct shell *self,
    struct my_shell_char_vector *line_buffer, shell_char_t *result)
{
    while (true) {
        if (!shell_read_character(self, true, result))
            return false;
        if (*result == SHELL_CHAR_ERROR || *result == '\n')
            break;
        *result &= SHELL_CHAR_NOT_QUOTED;
        if (*result != '\0')
            my_shell_char_vector_append_single(line_buffer, *result);
    }
    return true;
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_line_loop(struct shell *self,
    const shell_char_t *stop_line)
{
    struct my_shell_char_vector *line_buffer = my_shell_char_vector_new();
    shell_char_t c;

    while (true) {
        my_shell_char_vector_resize(line_buffer, 0);
        if (!do_single_line(self, line_buffer, &c)) {
            my_shell_char_vector_free(line_buffer);
            return false;
        }
        if (c == SHELL_CHAR_ERROR && line_buffer->size != 0)
            c = '\n';
        my_shell_char_vector_append_single(line_buffer, '\0');
        if (c == SHELL_CHAR_ERROR || shell_char_strcmp(line_buffer->data,
            stop_line) == 0)
            break;
        print_line_to_stdin(line_buffer);
    }
    my_shell_char_vector_free(line_buffer);
    return true;
}

// TODO Add proper error handling here instead of forcing an exit
bool shell_heredoc(struct shell *self, const shell_char_t *stop_line)
{
    char heredoc_name[] = "/tmp/sh.XXXXXX";

    shell_close(STDIN_FILENO);
    if (mkstemp(heredoc_name) == -1) {
        shell_set_error(self, SHELL_ERROR_SYSTEM, heredoc_name,
            strerror(errno));
        return false;
    }
    my_unlink(heredoc_name);
    if (!do_line_loop(self, stop_line))
        return false;
    my_lseek(STDIN_FILENO, 0, SEEK_SET);
    return true;
}
