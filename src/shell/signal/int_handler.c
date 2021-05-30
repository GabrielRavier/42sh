/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines int_handler
*/

#include "../signal.h"

void shell_signal_int_handler(MY_ATTR_UNUSED int signal)
{
    g_shell_signal.sigint_pending = true;
}
