/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines process_int
*/

#include "../signal.h"
#include "../purge_output_buffer.h"
#include "../putchar.h"
#include "../set_error.h"

bool shell_signal_process_int(struct shell *self, bool do_newline)
{
    shell_purge_output_buffer(self);
    if (self->input_is_tty && do_newline)
        shell_putchar(self, '\n');
    shell_set_error(self, SHELL_ERROR_FLAG_SILENT);
    return false;
}
