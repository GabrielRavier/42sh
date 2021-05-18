/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_cpy
*/

#include "../shell_char.h"

shell_char_t **shell_char_strv_cpy(shell_char_t **dest, shell_char_t **src)
{
    shell_char_t **i = dest;

    do
        *i++ = *src++;
    while (i[-1] != NULL);
    return dest;
}
