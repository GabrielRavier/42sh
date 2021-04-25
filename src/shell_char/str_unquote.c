/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines str_unquote
*/

#include "../shell_char.h"

shell_char_t *shell_char_str_unquote(shell_char_t *str)
{
    if (str == NULL)
        return NULL;
    for (shell_char_t *i = str; *i != '\0'; ++i)
        if ((*i & 0xF0000000) != 0xF0000000)
            *i &= SHELL_CHAR_NOT_QUOTE;
    return str;
}
