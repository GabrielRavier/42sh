/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines decr_disable
*/

#include "../signal.h"

bool shell_signal_decr_disable(struct shell *self, int *disable_sig)
{
    if (--*disable_sig == 0)
        if (!shell_signal_handle_pending(self))
            return false;
    return true;
}
