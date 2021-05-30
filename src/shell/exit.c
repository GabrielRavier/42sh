/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines exit
*/

#include "exit.h"
#include "flush_output_buffer.h"
#include "tty.h"
#include <stdlib.h>

void shell_exit(struct shell *self, int status)
{
    (void)self;
    shell_tty_ungrab(self);
    exit(status);
}
