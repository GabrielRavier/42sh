/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines read_character
*/

#include "read_character.h"
#include "exit_from_status.h"
#include "proc.h"
#include "read.h"
#include "set_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

MY_ATTR_WARN_UNUSED_RESULT static bool do_peek(struct shell *self,
    shell_char_t *result)
{
    shell_char_t peek_read_result;

    if (self->peek_read != 0) {
        peek_read_result = self->peek_read;
        self->peek_read = 0;
        *result = peek_read_result;
        return true;
    }
    return false;
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_eof(struct shell *self)
{
    struct termios term_attr;
    pid_t tty_pgrp;

    if (tcgetattr(self->input_fd, &term_attr) == 0 &&
        (term_attr.c_lflag & ICANON)) {
        if (self->terminal_pgrp != -1) {
            tty_pgrp = tcgetpgrp(SHELL_TTY_FD);
            if (tty_pgrp != -1 && self->terminal_pgrp != tty_pgrp) {
                tcsetpgrp(SHELL_TTY_FD, self->terminal_pgrp);
                kill(-tty_pgrp, SIGHUP);
                return true;
            }
        }
    }
    if (self->check_stop == 0 && !shell_proc_any_stopped(self, true))
        return false;
    self->done_input = true;
    shell_set_error(self, SHELL_ERROR_FLAG_SILENT);
    return false;
}

bool shell_read_character(struct shell *self, bool want_eof,
    shell_char_t *result)
{
    char read_char;
    ssize_t read_result;

    if (do_peek(self, result))
        return true;
    do {
        if (!shell_read(&((sr_opts_t){self, self->input_fd, &read_char, sizeof(
            read_char), &read_result})))
            return false;
        if (read_result != sizeof(read_char)) {
            if (want_eof) {
                *result = SHELL_CHAR_ERROR;
                return true;
            }
            if (!do_eof(self))
                return false;
        }
    } while (read_char == '\0');
    *result = read_char;
    return true;
}
