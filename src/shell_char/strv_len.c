/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_len
*/

#include "../shell_char.h"

size_t shell_char_strv_len(const shell_char_t **strv)
{
    size_t result = 0;

    while (*strv++ != NULL)
        ++result;
    return result;
}
