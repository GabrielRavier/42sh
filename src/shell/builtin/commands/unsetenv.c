/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin unsetenv
*/

#include "../commands.h"
#include "../../set_error.h"
#include "my/stdlib.h"
#include <string.h>
#include <errno.h>

void shell_builtin_unsetenv(struct shell *self, shell_char_t **argv)
{
    char *current_name;

    for (shell_char_t *const *arg_it = &argv[1]; *arg_it; ++arg_it) {
        current_name = shell_char_xstrdup_to_c(*arg_it);
        if (my_unsetenv(current_name) < 0) {
            shell_set_error(self, SHELL_ERROR_SYSTEM, "unsetenv",
                strerror(errno));
            my_free(current_name);
            return;
        }
        my_free(current_name);
    }
}
