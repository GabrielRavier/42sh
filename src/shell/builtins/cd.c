/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin cd
*/

#include "functions.h"
#include "../../error.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

static bool do_it(struct shell *self, const char *destination_from_arg)
{
    if (destination_from_arg) {
        if (chdir(destination_from_arg) != 0) {
            my_dprintf(STDERR_FILENO, "%s: %s.\n", destination_from_arg,
                strerror(errno));
            return (false);
        }
    } else if ((self->arguments[1] != NULL || my_getenv("HOME") != NULL) &&
        (chdir(self->arguments[1] ?: my_getenv("HOME")) != 0)) {
        error("cd: Can't change to home directory.");
        return (false);
    }
    return (true);
}

int shell_builtin_cd(struct shell *self)
{
    char *current_working_directory = getcwd(NULL, 0);
    const char *destination_from_arg = self->arguments[1] == NULL ? NULL :
        (my_strcmp(self->arguments[1], "-") == 0) ? (my_getenv("owd") ?: "") :
        self->arguments[1];

    if (!do_it(self, destination_from_arg)) {
        free(current_working_directory);
        return (1);
    }
    my_setenv("owd", current_working_directory, 1);
    free(current_working_directory);
    current_working_directory = getcwd(NULL, 0);
    my_setenv("PWD", current_working_directory, 1);
    free(current_working_directory);
    return (0);
}
