/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin setenv
*/

#include "../commands.h"
#include "../../set_error.h"
#include "my/stdlib.h"
#include "my/ctype.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

static bool check_args(struct shell *self, shell_char_t **argv)
{
    if (!my_isalpha(argv[1][0]) && argv[1][0] != '_') {
        shell_set_error(self, SHELL_ERROR_VAR_NAME_MUST_BEGIN_LETTER);
        return (false);
    }
    for (size_t i = 0; argv[1][i]; ++i)
        if (!my_isalnum(argv[1][i]) && argv[1][i] != '_' && argv[1][i] != '.') {
            shell_set_error(self, SHELL_ERROR_VAR_NAME_MUST_CONTAIN_ALNUM);
            return (false);
        }
    return (true);
}

void shell_builtin_setenv(struct shell *self, shell_char_t **argv)
{
    MY_CLEANUP_FREE char *var_name = NULL;
    MY_CLEANUP_FREE char *value = NULL;

    if (argv[1] == NULL) {
        shell_builtin_printenv(self, argv);
        return;
    }
    if (!check_args(self, argv))
        return;
    var_name = shell_char_xstrdup_to_c(argv[1]);
    value = argv[2] ? shell_char_xstrdup_to_c(argv[2]) : "";
    if (my_setenv(var_name, value, 1) < 0)
        shell_set_error(self, SHELL_ERROR_SYSTEM, "setenv", strerror(errno));
    value = argv[2] ? value : NULL;
    return;
}
