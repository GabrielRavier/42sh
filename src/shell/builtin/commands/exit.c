/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin exit
*/

#include "../commands.h"
#include "../../input_set_eof.h"
#include "../../close.h"
#include "my/stdlib.h"

// self->done_input = true is a HACK (remove later probably)
void shell_builtin_exit(struct shell *self, shell_char_t **argv)
{
    if (self->check_stop == 0 && self->input_is_tty)
        if (!shell_proc_any_stopped(self, false))
            return;
    if (argv[1] != NULL)
        self->last_command_exit_status = my_strtol(
            shell_char_static_xstrdup_to_c(argv[1]), NULL, 10);
    shell_input_set_eof(self);
    shell_close(self->input_fd);
    self->done_input = true;
}
