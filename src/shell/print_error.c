/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines print_error
*/

#include "print_error.h"
#include "flush_output_buffer.h"
#include "printf.h"
#include "exit.h"
#include "fix_error.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <stdlib.h>

void shell_print_error(struct shell *self)
{
    if (!self->error.is_silent) {
        shell_flush_output_buffer(self);
        self->handling_error = true;
        if (self->error.display_name)
            shell_printf(self, "%s: ", self->error_program_name);
        shell_printf(self, "%s.\n", self->error.text != NULL ?
            self->error.text : "No error to print", self->error_output_fd);
    }
    if (self->error.text != NULL) {
        my_free(self->error.text);
        self->error.text = NULL;
    }
    self->error.display_name = false;
    self->error.is_silent = false;
    shell_fix_error(self);
}
