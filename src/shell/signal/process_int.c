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
#include "../builtin/commands.h"

static shell_char_t JOBS[] = {'j', 'o', 'b', 's', '\0'};
static shell_char_t *JOBS_ARGV[2] = {JOBS, NULL};

bool shell_signal_process_int(struct shell *self, bool do_newline)
{
    if (self->should_set_interrupts && self->print_jobs_on_int) {
        self->print_jobs_on_int = false;
        shell_putchar(self, '\n');
        shell_builtin_jobs(self, JOBS_ARGV);
        shell_set_error(self, SHELL_ERROR_FLAG_NAME | SHELL_ERROR_INTERRUPTED);
        return false;
    }
    shell_purge_output_buffer(self);
    if (self->input_is_tty && do_newline)
        shell_putchar(self, '\n');
    shell_set_error(self, SHELL_ERROR_FLAG_SILENT);
    return false;
}
