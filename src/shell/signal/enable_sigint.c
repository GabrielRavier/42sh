/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines enable_sigint
*/

#include "../signal.h"

bool shell_signal_enable_sigint(struct shell *self, int *old_disable_sigint)
{
    *old_disable_sigint = self->disable_sigint;
    self->disable_sigint = 0;
    if (!shell_signal_handle_pending(self)) {
        self->disable_sigint = *old_disable_sigint;
        return false;
    }
    return true;
}
