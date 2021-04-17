/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines set_error
*/

#pragma once

#include "../shell.h"
#include "my/assert.h"
#include "my/stdio.h"
#include "my/string.h"
#include <stdarg.h>

static const char *const SHELL_SET_ERROR_FORMATS[SHELL_ERROR_LAST_ERROR] = {
    NULL,
    "Missing name for redirect",
    "Ambiguous output redirect",
    "Ambiguous input redirect",
    "Invalid null command",
    "No more processes",
    "No home directory",
    "Too many arguments",
    "%s: %s",
    "Can't change to home directory",
    "Variable name must begin with a letter",
    "Variable name must contain alphanumeric characters",
    "Too few arguments",
    "Can't make pipe",
};

static inline void shell_set_error(struct shell *self,
    enum shell_error_type error, ...)
{
    va_list arg_list;

    if (self->error == NULL) {
        MY_ASSERT(error > 0 && error < SHELL_ERROR_LAST_ERROR);
        va_start(arg_list, error);
        if (my_vasprintf(&self->error, SHELL_SET_ERROR_FORMATS[error],
            arg_list) < 0)
            self->error = my_xstrdup("Couldn't make error message");
        va_end(arg_list);
    }
}
