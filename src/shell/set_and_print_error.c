/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_and_print_error
*/

#include "set_and_print_error.h"
#include "vset_error.h"
#include "print_error.h"
#include <stdarg.h>

void shell_set_and_print_error(struct shell *self, enum shell_error_type error,
    ...)
{
    va_list arguments;

    va_start(arguments, error);
    shell_vset_error(self, error, arguments);
    va_end(arguments);
    shell_print_error(self);
}
