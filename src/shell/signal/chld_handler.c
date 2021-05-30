/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines chld_handler
*/

#include "../signal.h"

void shell_signal_chld_handler(MY_ATTR_UNUSED int signal)
{
    g_shell_signal.sigchld_pending = true;
}
