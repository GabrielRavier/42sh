/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin env
*/

#include "../commands.h"

void shell_builtin_env(struct shell *shell, shell_char_t **argv)
{
    shell_builtin_printenv(shell, argv);
}
