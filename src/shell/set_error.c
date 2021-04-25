/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines set_error
*/

#include "set_error.h"
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
    "Directory stack not that deep",
    "Badly formed number",
    "Usage: %s [-%s]%s",
    "Unknown user: %s",
    "No $home variable set",
    "Ambiguous",
};

void shell_set_error(struct shell *self,
    enum shell_error_type error, ...)
{
    va_list arg_list;
    int flags = error & SHELL_ERROR_FLAG_MASK;

    error &= ~SHELL_ERROR_FLAG_MASK;
    if (self->error == NULL) {
        MY_ASSERT(error > 0 && error < SHELL_ERROR_LAST_ERROR);
        va_start(arg_list, error);
        if (my_vasprintf(&self->error, SHELL_SET_ERROR_FORMATS[error],
            arg_list) < 0)
            self->error = my_xstrdup("Couldn't make error message");
        va_end(arg_list);
        if (flags & SHELL_ERROR_FLAG_NAME)
            if (my_asprintf(&self->error, "%s: %s", self->error_program_name,
                self->error) < 0)
                self->error = my_xstrdup("Couldn't make error message");
    }
}
