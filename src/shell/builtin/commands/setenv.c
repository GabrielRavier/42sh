/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin setenv
*/

#include "../commands.h"
#include "../../set_error.h"
#include "../../glob.h"
#include "../../setenv.h"
#include "../../import_env_path.h"
#include "my/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

static const shell_char_t NUL = '\0';
static const shell_char_t PATH[] = {'P', 'A', 'T', 'H', '\0'};

static bool check_args(struct shell *self, shell_char_t **argv)
{
    if (!shell_char_is_letter(argv[1][0])) {
        shell_set_error(self, SHELL_ERROR_VAR_NAME_MUST_BEGIN_LETTER |
            SHELL_ERROR_FLAG_NAME);
        return false;
    }
    for (size_t i = 0; argv[1][i] != '\0'; ++i)
        if (!shell_char_isalnum(argv[1][i]) && argv[1][i] != '.') {
            shell_set_error(self, SHELL_ERROR_VAR_NAME_MUST_CONTAIN_ALNUM |
                SHELL_ERROR_FLAG_NAME);
            return false;
        }
    return true;
}

void shell_builtin_setenv(struct shell *self, shell_char_t **argv)
{
    shell_char_t *value;

    if (argv[1] == NULL) {
        shell_builtin_printenv(self, argv);
        return;
    }
    if (!check_args(self, argv) || !shell_glob_str(self, argv[2] != NULL ?
        argv[2] : &NUL, SHELL_GLOB_STR_FLAG_APPEND, &value))
        return;
    shell_setenv(argv[1], value);
    if (shell_char_strcmp(argv[1], PATH) == 0)
        shell_import_env_path(self, value);
    my_free(value);
}
