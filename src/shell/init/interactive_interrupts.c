/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines interrupts
*/

#include "../init.h"
#include "../signal.h"

void shell_init_interactive_interrupts(struct shell *self)
{
    signal(SIGQUIT, SIG_IGN);
    self->disable_sigint = 1;
    shell_signal_set_interrupting_handler(SIGINT, shell_signal_int_handler);
    signal(SIGTERM, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}
