/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_interrupting_handler
*/

#include "../signal.h"
#include <signal.h>

void shell_signal_set_interrupting_handler(int signal, void (*function)(int))
{
    struct sigaction action = {.sa_handler = function, .sa_flags = 0};
    sigset_t set_with_signal;

    sigemptyset(&action.sa_mask);
    if (sigaction(signal, &action, NULL) == 0) {
        sigemptyset(&set_with_signal);
        sigaddset(&set_with_signal, signal);
        sigprocmask(SIG_UNBLOCK, &set_with_signal, NULL);
    }
}
