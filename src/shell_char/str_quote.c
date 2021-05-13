/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines str_quote
*/

#include "../shell_char.h"

shell_char_t *shell_char_str_quote(shell_char_t *str)
{
    if (str == NULL)
        return NULL;
    for (shell_char_t *i = str; *i != '\0'; ++i)
        if ((*i & 0xFFFFFF80) == 0)
            *i |= SHELL_CHAR_QUOTED;
    return str;
}
