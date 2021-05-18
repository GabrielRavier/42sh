/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines vset_error
*/

#include "vset_error.h"
#include "my/assert.h"
#include "my/stdio.h"

// Must be synchronized with the error enum in error.h
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
    "Directory stack not that deep",
    "Badly formed number",
    "Usage: %s [-%s]%s",
    "Unknown user: %s",
    "No $home variable set",
    "Ambiguous",
    "No match",
    "Unmatched '%c'",
    "%s",
    "Command not found",
    "%s: %s. Wrong Architecture",
};

// If the assert fails, we're gonna crash anyway
void shell_vset_error(struct shell *self, enum shell_error_type error,
    va_list arguments)
{
    int flags = error & SHELL_ERROR_FLAG_MASK;

    error &= ~SHELL_ERROR_FLAG_MASK;
    if (self->error == NULL) {
        MY_ASSERT(error > 0 && error < SHELL_ERROR_LAST_ERROR);
        my_xvasprintf(&self->error, SHELL_SET_ERROR_FORMATS[error], arguments);
        if (flags & SHELL_ERROR_FLAG_NAME)
            my_xasprintf(&self->error, "%s: %s", self->error_program_name,
                self->error);
    }
}
