/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_error
*/

#pragma once

#include "../shell.h"
#include <stdarg.h>

void shell_vset_error(struct shell *self, enum shell_error_type error,
    va_list arguments);
