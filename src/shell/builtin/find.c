/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines find
*/

#include "../builtin.h"
#include "commands.h"
#include "my/cpp-like/iterator.h"
#include "my/stdlib.h"

// Must be sorted, otherwise the bsearch in find won't work properly
static const struct shell_builtin builtins[] = {
    {"cd", shell_builtin_cd, 0, SIZE_MAX},
    {"chdir", shell_builtin_cd, 0, SIZE_MAX},
    {"env", shell_builtin_env, 0, SIZE_MAX},
    {"exit", shell_builtin_exit, 0, SIZE_MAX},
    {"printenv", shell_builtin_printenv, 0, SIZE_MAX},
    {"setenv", shell_builtin_setenv, 0, 2},
    {"unsetenv", shell_builtin_unsetenv, 1, SIZE_MAX},
};

static int cmp_command_name_builtin(const void *command_name_param,
    const void *builtin_param)
{
    const shell_char_t *command_name = command_name_param;
    const struct shell_builtin *builtin = builtin_param;

    return shell_char_cstrcmp_ignore_quote(command_name, builtin->name);
}

struct shell_builtin *shell_builtin_find(struct shell_parse_tree *parse_tree)
{
    const shell_char_t *command_name = parse_tree->argv[0];

    if (*command_name & SHELL_CHAR_QUOTED)
        return NULL;
    return my_bsearch(command_name, &builtins[0], MY_ARRAY_SIZE(builtins),
        sizeof(builtins[0]), cmp_command_name_builtin);
}
