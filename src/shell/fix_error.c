/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines fix_error
*/

#include "fix_error.h"
#include "exit.h"
#include "input_set_eof.h"

void shell_fix_error(struct shell *self)
{
    self->child_io_fds_setup = false;
    if (self->child_depth != 0)
        shell_exit(self, 1);
    shell_input_set_eof(self);
    self->last_command_exit_status = 1;
}
