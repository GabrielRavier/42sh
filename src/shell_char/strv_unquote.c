/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines strv_trim
*/

#include "../shell_char.h"

void shell_char_strv_unquote(shell_char_t **strv)
{
    while (*strv != NULL)
        for (shell_char_t *i = *strv++; *i != '\0'; ++i)
            *i &= SHELL_CHAR_NOT_QUOTE;
}
