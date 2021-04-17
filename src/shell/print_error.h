/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines print_error
*/

#pragma once

#include "../shell.h"
#include "my/assert.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <stdlib.h>
#include <unistd.h>

static inline void shell_print_error(struct shell *self, bool do_exit)
{
    my_dputs(self->error ? self->error : "No error to print",
        self->error_output_fd);
    my_dputs(".\n", self->error_output_fd);
    my_free(self->error);
    self->error = NULL;
    if (do_exit)
        exit(1);
}
