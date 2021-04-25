/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines str_get_flags
*/

#include "../glob.h"

int shell_glob_strv_get_flags(const shell_char_t **strv)
{
    int result = SHELL_GLOB_FLAG_NONE;

    for (const shell_char_t *i = *strv; i != NULL; i = *++strv)
        if (*i == '~')
            result |= SHELL_GLOB_FLAG_TCSH;
    return result;
}
