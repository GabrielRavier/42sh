/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines process
*/

#include "process.h"
#include "do_line.h"
#include "my/stdio.h"
#include <unistd.h>

void shell_process(struct shell *self)
{
    while (true) {
        if (self->input_is_tty)
            my_dputs("> ", self->output_fd);
        shell_do_line(self);
    }
}
