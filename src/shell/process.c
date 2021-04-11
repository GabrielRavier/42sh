/*
** EPITECH PROJECT, 2021
** mysh
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
        if (self->is_interactive)
            my_dputs("> ", STDOUT_FILENO);
        shell_do_line(self);
    }
}
