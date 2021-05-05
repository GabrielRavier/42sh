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
    shell_flush_output_buffer(self);
    self->handling_error = true;
    shell_printf(self, "%s.\n", self->error != NULL ? self->error :
        "No error to print", self->error_output_fd);
    my_free(self->error);
    self->error = NULL;
    shell_fix_error(self);
    self->handling_error = false;
}
