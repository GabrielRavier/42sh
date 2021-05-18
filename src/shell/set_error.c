/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_error
*/

#include "set_error.h"
#include "vset_error.h"

void shell_set_error(struct shell *self, enum shell_error_type error, ...)
{
    va_list arguments;

    va_start(arguments, error);
    shell_vset_error(self, error, arguments);
    va_end(arguments);
}
