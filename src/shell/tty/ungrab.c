/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines ungrab
*/

#include "../tty.h"
#include <unistd.h>

void shell_tty_ungrab(struct shell *self)
{
    if (self->terminal_pgrp > 0 && self->original_pgrp != self->pgrp) {
        setpgid(0, self->original_pgrp);
        tcsetpgrp(SHELL_TTY_FD, self->original_pgrp);
    }
}
