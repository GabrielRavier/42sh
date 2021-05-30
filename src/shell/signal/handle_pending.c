/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines handle_pending
*/

#include "../signal.h"
#include "../printf.h"
#include "my/assert.h"

bool shell_signal_handle_pending(struct shell *self)
{
    bool result;

    SHELL_DEBUG_PRINTF(self, "Entered shell_signal_handle_pending with "
        "disable_sigint %d, disable_sigchld %d\n", self->disable_sigint,
        self->disable_sigchld);
    if (self->disable_sigint == 0 && g_shell_signal.sigint_pending) {
        g_shell_signal.sigint_pending = false;
        ++self->handling_interrupt;
        MY_ASSERT(shell_signal_process_int(self, true) == false);
        --self->handling_interrupt;
        return false;
    }
    if (self->disable_sigchld == 0 && g_shell_signal.sigchld_pending) {
        g_shell_signal.sigchld_pending = false;
        ++self->handling_interrupt;
        result = shell_signal_process_chld(self);
        --self->handling_interrupt;
        if (result == false)
            return false;
    }
    return true;
}
